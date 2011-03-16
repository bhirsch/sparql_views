<?php
/**
 * Handler for a subject.
 */
class sparql_views_handler_field_subject extends sparql_views_handler_field {
  /**
  * Called to add the field to a query.
  */
  function query() {
    $this->field_alias = $this->real_field;
    $this->query->select_fields[] = $this->real_field;
  }
}