<?php
/**
 * @defgroup views_argument_handlers Handlers for arguments
 * @{
 */

/**
 * Base class for arguments.
 */
class sparql_views_handler_argument extends views_handler_argument {
  // We will use the value type and language form elements for getting
  // necessary info about replacements that this argument makes.
  var $selected_sparql_options = array('value_type', 'language');

  function option_definition() {
    $options = parent::option_definition();
    $options['source_field'] = array('default' => '');
    // Attach the SPARQL specific options.
    $options = _sparql_views_attach_form_options($options, $this->selected_sparql_options);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $fields = array();
    $instance_info = field_info_instances('node');
    foreach ($instance_info as $bundle) {
      foreach ($bundle as $field_name => $field_info) {
        $fields[$field_name] = check_plain(t($field_info['label']));
      }
    }
    // Attach the SPARQL specific form elements.
    $form = _sparql_views_attach_form_elements($form, $this->options, $this->selected_sparql_options);
    $form['sparql_options']['source_field'] = array(
      '#type' => 'select',
      '#title' => t('Source Field'),
      '#options' => $fields,
      '#default_value' => $this->options['sparql_options']['source_field'],
      '#description' => t('The variable in the query will be replaced with the value of this field on the node.'),
      '#weight' => -1,
    );
  }

  /**
   * Set up the query for this argument.
   *
   * The argument sent may be found at $this->argument.
   */
  function query() {
    // If the argument is set as the only argument and it is accessing a node,
    // change the argument to the nid.
    if ($this->argument == 'node') {
      $argument = $this->view->args[1];
    }
    // We need to load the node, so we require that the arg is numeric.
    if (!is_numeric($argument)) {
      return FALSE;
    }
    $node = node_load($argument);
    if (!$node) {
      return FALSE;
    }
    $source_field = $this->options['sparql_options']['source_field'];
    $field = field_get_items('node', $node, $source_field);
    $replacement = $field[0]['value'];
    $value_type = $this->options['sparql_options']['value_type'];
    $language = $this->options['sparql_options']['language'];
    $this->query->add_replacement($this->options['field'], $replacement, $value_type, $language);
  }
}