<?php
/**
 * @file
 * Views filter handler to display UI for WHERE clauses and prepare them for
 * the query.
 */

class sparql_views_handler_filter_field_value extends views_handler_filter_string{

  function option_definition() {
    $options = parent::option_definition();

    $options['value_type'] = array('default' => 'string');

    return $options;
  }
  
  /**
   * This kind of construct makes it relatively easy for a child class
   * to add or remove functionality by overriding this function and
   * adding/removing items from this array.
   */
  function operators() {
    $operators = array(
      '=' => array(
        'title' => t('Is equal to'),
        'short' => t('='),
        'method' => 'op_equal',
        'values' => 1,
      ),
    );
    return $operators;
  }

  function admin_summary() {
  if (!empty($this->options['exposed'])) {
      return t('exposed');
    }
    $output .= ' '. check_plain($this->value['subject'] .' '. $this->value['predicate'] .' '. $this->value['object']);
    return $output;
  }
  
  function value_form(&$form, &$form_state) {
    // We have to make some choices when creating this as an exposed
    // filter form. For example, if the operator is locked and thus
    // not rendered, we can't render dependencies; instead we only
    // render the form items we need.
    $which = 'all';
    if (!empty($form['operator'])) {
      $source = ($form['operator']['#type'] == 'radios') ? 'radio:options[operator]' : 'edit-options-operator';
    }
    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];

      if (empty($this->options['expose']['use_operator']) || empty($this->options['expose']['operator'])) {
        // exposed and locked.
        $which = in_array($this->operator, $this->operator_values(1)) ? 'value' : 'none';
      }
      else {
        $source = 'edit-' . drupal_html_id($this->options['expose']['operator']);
      }
    }

    if ($which == 'all' || $which == 'value') {
      $form['value'] = array(
        '#type' => 'textfield',
        '#title' => t('Value'),
        '#size' => 60,
        '#default_value' => $this->value,
      );
      if (!empty($form_state['exposed']) && !isset($form_state['input'][$identifier])) {
        $form_state['input'][$identifier] = $this->value;
      }

      if ($which == 'all') {
        $form['value'] += array(
          '#process' => array('ctools_dependent_process'),
          '#dependency' => array($source => $this->operator_values(1)),
        );
      }
    }

    if (!isset($form['value'])) {
      // Ensure there is something in the 'value'.
      $form['value'] = array(
        '#type' => 'value',
        '#value' => NULL
      );
    }
    $form['value_type'] = array(
      '#type' => 'select',
      '#title' => t('Value Type'),
      '#options' => array('string' => 'String', 'uri' => 'URI', 'number' => 'Number'),
      '#default_value' => $this->options['value_type'],
      '#prefix' => '<div class="views-right-70">',
      '#suffix' => '</div>',
    );
  }

  function query() {
    $field_name = $this->real_field;
    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}($field_name);
    }
  }
  
  function op_equal($field_name) {
    // If this is a URI, we have to replace the variable with the URI. We may
    // also need to replace the URI value back into the results.
    switch($this->options['value_type']){
      case 'uri':
        $replacement = $this->options['value'];
        $this->query->add_replacement($field_name, "<$replacement>");
        break;
      case 'string':
        $replacement = $this->options['value'];
        
        break;
    }
  }
}
