<?php
/**
 * @defgroup views_argument_handlers Handlers for arguments
 * @{
 */

/**
 * Base class for arguments.
 */
class sparql_views_handler_argument extends views_handler_argument {
  /**
   * Set up the query for this argument.
   *
   * The argument sent may be found at $this->argument.
   */
  function query() {
  }
}