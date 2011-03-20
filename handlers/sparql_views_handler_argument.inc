<?php
/**
 * @defgroup views_argument_handlers Handlers for arguments
 * @{
 */

/**
 * Base class for arguments.
 */
class sparql_views_handler_argument extends views_handler_argument {
  function option_definition() {
    $options = parent::option_definition();
    $options['source_field'] = array('default' => '');
    $options['value_type'] = array('default' => '');
    $options['language'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $fields = array();
    $languages = _sparql_views_get_language_list();
    $instance_info = field_info_instances('node');
    foreach ($instance_info as $bundle) {
      foreach ($bundle as $field_name => $field_info) {
        $fields[$field_name] = check_plain(t($field_info['label']));
      }
    }
    $form['sparql_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('SPARQL Settings'),
      '#weight' => 0,
    );
    $form['sparql_settings']['source_field'] = array(
      '#type' => 'select',
      '#title' => t('Source Field'),
      '#options' => $fields,
      '#default_value' => $this->options['source_field'],
      '#description' => t('The variable in the query will be replaced with the value of this field on the node.'),
    );
    $form['sparql_settings']['value_type'] = array(
      '#type' => 'select',
      '#title' => t('Value Type'),
      '#options' => _sparql_views_get_variable_value_types(),
      '#default_value' => $this->options['value_type'],
    );
    $form['sparql_settings']['language'] = array(
      '#type' => 'select',
      '#title' => t('Language'),
      '#options' => $languages,
      '#default_value' => $this->options['language'],
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
    
    $source_field = $this->options['source_field'];
    $field = field_get_items('node', $node, $source_field);
    $field_value = $field[0]['value'];
    switch($this->options['value_type']){
      case 'uri':
        $replacement = "<$field_value>";
        break;
      case 'string':
        $language = $this->options['language'];
        $replacement = '"' . $field_value . '"';
        if (isset($language)) {
          $replacement .= "@$language";
        }
        break;
    }
    $this->query->add_replacement($this->options['field'], $replacement);
  }
}