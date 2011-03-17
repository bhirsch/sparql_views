<?php
/**
 * Base field handler that has no options and renders an unformatted field.
 *
 * Definition terms:
 * - additional fields: An array of fields that should be added to the query
 *                      for some purpose. The array is in the form of:
 *                      array('identifier' => array('table' => tablename,
 *                      'field' => fieldname); as many fields as are necessary
 *                      may be in this array.
 * - click sortable: If TRUE, this field may be click sorted.
 */
class sparql_views_handler_field extends views_handler_field {
  /**
   * Called to add the field to a query.
   */
  function query() {
    $relationship = $this->options['relationship'];
    $subject = $relationship != 'none' ? $relationship : $this->definition['subject'];
    $this->field_alias = $this->real_field;
    $this->query->select_fields[] = $this->real_field;
    $this->query->triples[$subject]['pred_obj'][] = array('p' => $this->definition['rdf_mapping'][0], 'o' => $this->real_field);
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['label'] = array('default' => $this->definition['title'], 'translatable' => TRUE);
    $options['exclude'] = array('default' => FALSE, 'bool' => TRUE);
    $options['alter'] = array(
      'contains' => array(
        'alter_text' => array('default' => FALSE),
        'text' => array('default' => '', 'translatable' => TRUE),
        'make_link' => array('default' => FALSE),
        'path' => array('default' => '', 'translatable' => TRUE),
        'absolute' => array('default' => '', 'translatable' => FALSE),
        'alt' => array('default' => '', 'translatable' => TRUE),
        'rel' => array('default' => ''),
        'link_class' => array('default' => ''),
        'prefix' => array('default' => '', 'translatable' => TRUE),
        'suffix' => array('default' => '', 'translatable' => TRUE),
        'target' => array('default' => '', 'translatable' => TRUE),
        'trim' => array('default' => FALSE),
        'max_length' => array('default' => ''),
        'word_boundary' => array('default' => TRUE),
        'ellipsis' => array('default' => TRUE),
        'strip_tags' => array('default' => FALSE),
        'html' => array('default' => FALSE),
      ),
    );
    $options['element_type'] = array('default' => '');
    $options['element_class'] = array('default' => '');

    $options['element_label_type'] = array('default' => '');
    $options['element_label_class'] = array('default' => '');
    $options['element_label_colon'] = array('default' => TRUE);

    $options['element_wrapper_type'] = array('default' => '');
    $options['element_wrapper_class'] = array('default' => '');

    $options['element_default_classes'] = array('default' => TRUE);

    $options['empty'] = array('default' => '', 'translatable' => TRUE);
    $options['hide_empty'] = array('default' => FALSE);
    $options['empty_zero'] = array('default' => FALSE);

    return $options;
  }

  /**
   * Default options form that provides the label widget that all fields
   * should have.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }
}
