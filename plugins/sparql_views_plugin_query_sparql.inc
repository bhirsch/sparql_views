<?php
/**
 * Object used to create a SELECT query.
 */
class sparql_views_plugin_query_sparql extends views_plugin_query {
  /**
   * An array of fields which have been specified for selection. Fields may be
   * included in the triple patterns (i.e. in filters or for path traversal)
   * without being selected for retrieval.
   */
  var $select_fields = array();

  /**
   * An array of sections of the triple pattern. Each section is in itself
   * an array of pieces.
   */
  var $triples = array();

  /**
   * An array of URIs and resources that are used as replacements for variables.
   */
  var $replacements = array();

  /**
   * An array of filter functions and parameters.
   */
  var $filters = array();

  /**
   * A pager plugin that should be provided by the display.
   */
  var $pager = NULL;

  /**
   * Constructor; Create the basic query object and fill with default values.
   */
  function init($base_table, $base_field, $options) {
    parent::init($base_table, $base_field, $options);
    $this->base_table = $base_table;
    $this->base_field = $base_field;
    $this->unpack_options($this->options, $options);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['endpoint'] = array('default' => '');

    return $options;
  }
  
  function options_form(&$form, &$form_state) {
    $endpoints = entity_load('sparql_endpoint', FALSE);
    $ep_options = array();
    foreach($endpoints as $key => $value) {
      $ep_options[$value->endpoint] = $value->title;
    }
    $form['endpoint'] = array(
      '#type' => 'select',  
      '#options' => $ep_options,
      '#title' => t('SPARQL Endpoint'),
      '#default_value' => $this->options['endpoint'],
      '#description' => t("The SPARQL endpoint that you want to access."),
    );
  }

 /**
  * Generate a query and a countquery from all of the information supplied
  * to the object.
  *
  * @param $get_count
  *   Provide a countquery if this is true, otherwise provide a normal query.
  */
  function query($view, $get_count = FALSE) {
    $triple_pattern = '';
    $filters = '';
    $ns = rdf_get_namespaces();
    $bindings = array();
    $prefixes = '';
    $mynamespaces = array();

    // Create SELECT statement.
    $select = 'SELECT';
    foreach ($this->select_fields as $key => $field) {
      // Do not add variable to SELECT if it will be replaced with a value.
      if (!isset($this->replacements[$field])) {
        // Add a question mark before each variable.
        $select .= " ?$field";
      }
    }
    $where = '';
    foreach($this->triples as $s => $pattern) {
      $statements = array();
      $triple_pattern .= "?$s";
      foreach($pattern['pred_obj'] as $pred_obj) {
        $p = isset($this->replacements[$pred_obj['p']]) ? $this->replacements[$pred_obj['p']] : $pred_obj['p'];
        $o = isset($this->replacements[$pred_obj['o']]) ? $this->replacements[$pred_obj['o']] : '?' . $pred_obj['o'];
        $statements[] = " $p $o";
        $mynamespaces[] = _sparql_views_predicate_ns($p); 
      }
      $triple_pattern .= implode(';', $statements) . ".\n";
    }
    $mynamespaces = array_unique($mynamespaces);
    foreach($mynamespaces as $prefix) {
      $namespace = $ns[$prefix];
      $prefixes .= "PREFIX $prefix: <$namespace>\n";
    }
    foreach ($this->filters as $filter) {
      $filters .= "FILTER $filter\n";
    }
    $limit = isset($this->limit) ? "LIMIT $this->limit" : 'LIMIT 10';
    
    $query = $prefixes;
    $query .= $select . "\n";
    $query .= "WHERE {\n$triple_pattern $filters} \n";
    $query .= $limit;
    return $query;
  }

  /**
   * Let modules modify the query just prior to finalizing it.
   */
  function alter(&$view) {  }

  /**
   * Builds the necessary info to execute the query.
   */
  function build(&$view) {
    $view->init_pager();

    // Let the pager modify the query to add limits.
    $this->pager->query($view);

    $view->build_info['query'] = $this->query($view);
  }

  /**
   * Executes the query and fills the associated view object with according
   * values.
   *
   * Values to set: $view->result, $view->total_rows, $view->execute_time,
   * $view->pager['current_page'].
   */
  function execute(&$view) {  
    module_load_include('inc', 'rdfx', 'rdfx.sparql');
    $query = $view->build_info['query'];
    $endpoint = $this->options['endpoint'];
    $start = microtime(TRUE);
    $sparql_result = rdfx_sparql_request($query, $endpoint);
    $rows = $sparql_result['result']['rows'];
    $fields = $sparql_result['result']['variables'] ;
    foreach ($rows as $row) {
      $views_row = array();
      foreach($fields as $field) {
        $views_row[$field] = $row[$field];
      }
      $views_result[] = (object) $views_row;
    }
    $view->result = $views_result;
    $view->total_rows = count($views_result);
    $view->execute_time = microtime(TRUE) - $start;
    $view->pager['current_page'] = 0;
  }

  function add_field($subject, $predicate, $object) {
    $i = 1;
    $alias = $object;
    while (in_array($alias, $this->select_fields)) {
      $alias = $object . '_' . $i;
      $i++;
    }
    $this->select_fields[] = $alias;
    $this->triples[$subject]['pred_obj'][] = array('p' => $predicate, 'o' => $alias);
    return $alias;
  }

  function add_replacement($field_name, $replacement) {
    $this->replacements[$field_name] = $replacement;
  }

  function add_filter($function, $params) {
    $params = implode(', ',$params);
    $this->filters[] = "$function($params)";
  }

  /**
   * Add a signature to the query, if such a thing is feasible.
   *
   * This signature is something that can be used when perusing query logs to
   * discern where particular queries might be coming from.
   */
 // function add_signature(&$view) { }

  /**
   * Get aggregation info for group by queries.
   *
   * If NULL, aggregation is not allowed.
   */
 // function get_aggregation_info() { }

 // function options_validate(&$form, &$form_state) { }

  function validate() {
    if($this->options['endpoint'] == '') {
      return array('Please choose a SPARQL Endpoint from "Query settings"');
    }
  }
 // function options_submit(&$form, &$form_state) { }

 // function summary_title() {
 //   return t('Settings');
 // }

  /**
   * Set a LIMIT on the query, specifying a maximum number of results.
   */
  function set_limit($limit) {
    $this->limit = $limit;
  }

  /**
   * Set an OFFSET on the query, specifying a number of results to skip
   */
 // function set_offset($offset) {
 //   $this->offset = $offset;
 // }

 // /**
 //  * Render the pager, if necessary.
 //  */
 // function render_pager() {
 //   if (!empty($this->pager) && $this->pager->use_pager()) {
 //     $exposed_input = isset($this->view->exposed_data_raw) ? $this->view->exposed_data_raw : NULL;
 //     return $this->pager->render($exposed_input);
 //   }
 //   return '';
 // }
}
