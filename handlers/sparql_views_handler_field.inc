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
    $object = $this->real_field;
    $relationship = $this->options['relationship'];
    if ($relationship == 'none') {
      $subject = $this->definition['subject'];
    }
    else {
      $subject = $relationship;
    }
    $predicate = $this->definition['rdf_mapping'][0];
    $this->field_alias = $this->query->add_field($subject, $predicate, $object);
  }
}
