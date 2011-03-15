<?php
// $Id: varql_handler_field.inc,v 1.1 2010/12/28 01:30:12 rgeorgy Exp $

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
 // /**
 //  * Construct a new field handler.
 //  */
 // function construct() {
 //   parent::construct();

 //   $this->additional_fields = array();
 //   if (!empty($this->definition['additional fields'])) {
 //     $this->additional_fields = $this->definition['additional fields'];
 //   }

 //   if (!isset($this->options['exclude'])) {
 //     $this->options['exclude'] = '';
 //   }
 // }

 // /**
 //  * Determine if this field can allow advanced rendering.
 //  *
 //  * Fields can set this to FALSE if they do not wish to allow
 //  * token based rewriting or link-making.
 //  */
 // function allow_advanced_render() {
 //   return TRUE;
 // }

 // function init(&$view, &$options) {
 //   parent::init($view, $options);

 //   $this->options += array(
 //     'exclude' => FALSE,
 //   );
 // }

 // /**
 //  * Called to add the field to a query.
 //  */
function query() {
  $relationship = $this->options['relationship'];
  $subject = $relationship != 'none' ? $relationship : 'subject_1';
  $this->field_alias = $this->real_field;
  $this->query->select_fields[] = $this->real_field;
  $this->query->triples[$subject]['pred_obj'][] = array('p' => $this->definition['rdf_mapping']['predicates'][0], 'o' => $this->real_field);
}

 // /**
 //  * Add 'additional' fields to the query.
 //  *
 //  * @param $fields
 //  * An array of fields. The key is an identifier used to later find the
 //  * field alias used. The value is either a string in which case it's
 //  * assumed to be a field on this handler's table; or it's an array in the
 //  * form of
 //  * @code array('table' => $tablename, 'field' => $fieldname) @endcode
 //  */
 // function add_additional_fields($fields = NULL) {
 //   if (!isset($fields)) {
 //     // notice check
 //     if (empty($this->additional_fields)) {
 //       return;
 //     }
 //     $fields = $this->additional_fields;
 //   }
 //   if (!empty($fields) && is_array($fields)) {
 //     foreach ($fields as $identifier => $info) {
 //       if (is_array($info)) {
 //         if (isset($info['table'])) {
 //           $table_alias = $this->query->ensure_table($info['table'], $this->relationship);
 //         }
 //         else {
 //           $table_alias = $this->table_alias;
 //         }

 //         if (empty($table_alias)) {
 //           debug(t('Handler @handler tried to add additional_field @identifier but @table could not be added!', array('@handler' => $this->definition['handler'], '@identifier' => $identifier, '@table' => $info['table'])));
 //           $this->aliases[$identifier] = 'broken';
 //           continue;
 //         }

 //         $params = array();
 //         if (!empty($info['params'])) {
 //           $params = $info['params'];
 //         }

 //         $this->aliases[$identifier] = $this->query->add_field($table_alias, $info['field'], NULL, $params);
 //       }
 //       else {
 //         $this->aliases[$info] = $this->query->add_field($this->table_alias, $info);
 //       }
 //     }
 //   }
 // }

 // /**
 //  * Called to determine what to tell the clicksorter.
 //  */
 // function click_sort($order) {
 //   if (isset($this->field_alias)) {
 //     // Since fields should always have themselves already added, just
 //     // add a sort on the field.
 //     $this->query->add_orderby(NULL, NULL, $order, $this->field_alias);
 //   }
 // }

 // /**
 //  * Determine if this field is click sortable.
 //  */
 // function click_sortable() {
 //   return !empty($this->definition['click sortable']);
 // }

 // /**
 //  * Get this field's label.
 //  */
 // function label() {
 //   if (!isset($this->options['label'])) {
 //     return '';
 //   }
 //   return $this->options['label'];
 // }

 // /**
 //  * Return an HTML element based upon the field's element type.
 //  */
 // function element_type($none_supported = FALSE, $default_empty = FALSE) {
 //   if ($none_supported) {
 //     if ($this->options['element_type'] === '0') {
 //       return '';
 //     }
 //   }
 //   if ($this->options['element_type']) {
 //     return check_plain($this->options['element_type']);
 //   }

 //   if ($default_empty) {
 //     return '';
 //   }

 //   if (isset($this->definition['element type'])) {
 //     return $this->definition['element type'];
 //   }

 //   return 'span';
 // }

 // /**
 //  * Return an HTML element for the label based upon the field's element type.
 //  */
 // function element_label_type($none_supported = FALSE, $default_empty = FALSE) {
 //   if ($none_supported) {
 //     if ($this->options['element_label_type'] === '0') {
 //       return '';
 //     }
 //   }
 //   if ($this->options['element_label_type']) {
 //     return check_plain($this->options['element_label_type']);
 //   }

 //   if ($default_empty) {
 //     return '';
 //   }

 //   return 'span';
 // }

 // /**
 //  * Return an HTML element for the wrapper based upon the field's element type.
 //  */
 // function element_wrapper_type($none_supported = FALSE, $default_empty = FALSE) {
 //   if ($none_supported) {
 //     if ($this->options['element_wrapper_type'] === '0') {
 //       return 0;
 //     }
 //   }
 //   if ($this->options['element_wrapper_type']) {
 //     return check_plain($this->options['element_wrapper_type']);
 //   }

 //   if ($default_empty) {
 //     return '';
 //   }

 //   return 'div';
 // }

 // /**
 //  * Provide a list of elements valid for field HTML.
 //  *
 //  * This function can be overridden by fields that want more or fewer
 //  * elements available, though this seems like it would be an incredibly
 //  * rare occurence.
 //  */
 // function get_elements() {
 //   return array(
 //     '' => t('- Use default -'),
 //     '0' => t('- None -'),
 //     'div' => t('DIV'),
 //     'span' => t('SPAN'),
 //     'h1' => t('H1'),
 //     'h2' => t('H2'),
 //     'h3' => t('H3'),
 //     'h4' => t('H4'),
 //     'h5' => t('H5'),
 //     'h6' => t('H6'),
 //     'p' => t('P'),
 //     'strong' => t('STRONG'),
 //     'em' => t('EM'),
 //   );
 // }

 // /**
 //  * Return the class of the field.
 //  */
 // function element_classes() {
 //   $classes = $this->tokenize_value($this->options['element_class']);
 //   return drupal_clean_css_identifier($classes);
 // }

 // /**
 //  * Replace a value with tokens from the last field.
 //  *
 //  * This function actually figures out which field was last and uses its
 //  * tokens so they will all be available.
 //  */
 // function tokenize_value($value) {
 //   if (strpos($value, '[') !== FALSE || strpos($value, '!') !== FALSE || strpos($value, '%') !== FALSE) {
 //     $fake_item = array(
 //       'alter_text' => TRUE,
 //       'text' => $value,
 //     );

 //     // Get tokens from the last field.
 //     $last_field = end($this->view->field);
 //     if (isset($last_field->last_tokens)) {
 //       $tokens = $last_field->last_tokens;
 //     }
 //     else {
 //       $tokens = $last_field->get_render_tokens($fake_item);
 //     }

 //     $value = strip_tags($this->render_altered($fake_item, $tokens));
 //   }

 //   return $value;
 // }

 // /**
 //  * Return the class of the field's label.
 //  */
 // function element_label_classes() {
 //   return drupal_clean_css_identifier($this->options['element_label_class']);
 // }

 // /**
 //  * Return the class of the field's wrapper.
 //  */
 // function element_wrapper_classes() {
 //   return drupal_clean_css_identifier($this->options['element_wrapper_class']);
 // }

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

 // /**
 //  * Provide extra data to the administration form
 //  */
 // function admin_summary() {
 //   return $this->label();
 // }

 // /**
 //  * Run before any fields are rendered.
 //  *
 //  * This gives the handlers some time to set up before any handler has
 //  * been rendered.
 //  *
 //  * @param $values
 //  *   An array of all objects returned from the query.
 //  */
 // function pre_render(&$values) { }

 // /**
 //  * Render the field.
 //  *
 //  * @param $values
 //  *   The values retrieved from the database.
 //  */
 // function render($values) {
 //   $value = $values->{$this->field_alias};
 //   return check_plain($value);
 // }

 // /**
 //  * Render a field using advanced settings.
 //  *
 //  * This renders a field normally, then decides if render-as-link and
 //  * text-replacement rendering is necessary.
 //  */
 // function advanced_render($values) {
 //   if ($this->allow_advanced_render() && method_exists($this, 'render_item')) {
 //     $raw_items = $this->get_items($values);
 //   }
 //   else {
 //     $this->last_render = $value = $this->render($values);
 //     $this->original_value = $value;
 //   }

 //   if ($this->allow_advanced_render()) {
 //     $tokens = NULL;
 //     if (method_exists($this, 'render_item')) {
 //       $items = array();
 //       foreach ($raw_items as $count => $item) {
 //         $this->last_render = $this->render_item($count, $item);
 //         $this->original_value = $this->last_render;

 //         $alter = $item + $this->options['alter'];
 //         $items[] = $this->render_text($alter);
 //       }

 //       $value = $this->render_items($items);
 //     }
 //     else {
 //       $value = $this->render_text($this->options['alter']);
 //     }

 //     // This happens here so that render_as_link can get the unaltered value of
 //     // this field as a token rather than the altered value.
 //     $this->last_render = $value;
 //   }

 //   if (empty($this->last_render)) {
 //     if (($this->last_render !== 0 && $this->last_render !== '0') || !empty($this->options['empty_zero'])) {
 //       $alter = $this->options['alter'];
 //       $alter['alter_text'] = 1;
 //       $alter['text'] = $this->options['empty'];
 //       $this->last_render = $this->render_text($alter);
 //     }
 //   }

 //   return $this->last_render;
 // }

 // /**
 //  * Perform an advanced text render for the item.
 //  *
 //  * This is separated out as some fields may render lists, and this allows
 //  * each item to be handled individually.
 //  */
 // function render_text($alter) {
 //   $value = trim($this->last_render);

 //   if (!empty($alter['alter_text']) && $alter['text'] !== '') {
 //     $tokens = $this->get_render_tokens($alter);
 //     $value = $this->render_altered($alter, $tokens);
 //   }

 //   if ($this->options['hide_empty'] && empty($value) && ($value !== 0 || $this->options['empty_zero'])) {
 //     return '';
 //   }

 //   if (!empty($alter['strip_tags'])) {
 //     $value = strip_tags($value);
 //   }

 //   if (!empty($alter['trim']) && !empty($alter['max_length'])) {
 //     $value = $this->render_trim_text($alter, $value);
 //   }

 //   if (!empty($alter['make_link']) && !empty($alter['path'])) {
 //     if (!isset($tokens)) {
 //      $tokens = $this->get_render_tokens($alter);
 //     }
 //     $value = $this->render_as_link($alter, $value, $tokens);
 //   }

 //   return $value;
 // }

 // /**
 //  * Render this field as altered text, from a fieldset set by the user.
 //  */
 // function render_altered($alter, $tokens) {
 //   // Filter this right away as our substitutions are already sanitized.
 //   $value = filter_xss_admin($alter['text']);
 //   $value = strtr($value, $tokens);

 //   return $value;
 // }

 // /**
 //  * Trim the field down to the specified length.
 //  */
 // function render_trim_text($alter, $value) {
 //   if (!empty($alter['strip_tags'])) {
 //     // NOTE: It's possible that some external fields might override the
 //     // element type so if someone from, say, CCK runs into a bug here,
 //     // this may be why =)
 //     $this->definition['element type'] = 'span';
 //   }
 //   return views_trim_text($alter, $value);
 // }

 // /**
 //  * Render this field as a link, with the info from a fieldset set by
 //  * the user.
 //  */
 // function render_as_link($alter, $text, $tokens) {
 //   $value = '';

 //   if (!empty($alter['prefix'])) {
 //     $value .= filter_xss_admin(strtr($alter['prefix'], $tokens));
 //   }

 //   $options = array(
 //     'html' => TRUE,
 //     'absolute' => !empty($alter['absolute']) ? TRUE : FALSE,
 //   );

 //   // $path will be run through check_url() by l() so we do not need to
 //   // sanitize it ourselves.
 //   $path = $alter['path'];

 //   // html_entity_decode removes <front>, so check whether its different to front.
 //   if ($path != '<front>') {
 //     // Use strip tags as there should never be HTML in the path.
 //     // However, we need to preserve special characters like " that
 //     // were removed by check_plain().
 //     $path = strip_tags(html_entity_decode(strtr($path, $tokens)));
 //   }

 //   // If the path is empty do not build a link around the given text and return
 //   // it as is.
 //   if (empty($path)) {
 //     return $text;
 //   }

 //   // Parse the URL and move any query and fragment parameters out of the path.
 //   $url = parse_url($path);
 //   if (isset($url['query'])) {
 //     $path = strtr($path, array('?' . $url['query'] => ''));
 //     $options['query'] = drupal_get_query_array($url['query']);
 //   }
 //   if (isset($url['fragment'])) {
 //     $path = strtr($path, array('#' . $url['fragment'] => ''));
 //     // If the path is empty we want to have a fragment for the current site.
 //     if ($path == '') {
 //       $options['external'] = TRUE;
 //     }
 //     $options['fragment'] = $url['fragment'];
 //   }

 //   $alt = strtr($alter['alt'], $tokens);
 //   // Set the title attribute of the link only if it improves accessibility
 //   if ($alt && $alt != $text) {
 //     $options['attributes']['title'] = html_entity_decode($alt, ENT_QUOTES);
 //   }

 //   $class = strtr($alter['link_class'], $tokens);
 //   if ($class) {
 //     $options['attributes']['class'] = array($class);
 //   }

 //   if (!empty($alter['rel']) && $rel = strtr($alter['rel'], $tokens)) {
 //     $options['attributes']['rel'] = $rel;
 //   }

 //   $target = check_plain(trim(strtr($alter['target'],$tokens)));
 //   if (!empty($target)) {
 //     $options['attributes']['target'] = $target;
 //   }

 //   // If the query and fragment were programatically assigned overwrite any
 //   // parsed values.
 //   if (isset($alter['query'])) {
 //     // Convert the query to a string, perform token replacement, and then
 //     // convert back to an array form for l().
 //     $options['query'] = drupal_http_build_query($alter['query']);
 //     $options['query'] = strtr($options['query'], $tokens);
 //     $options['query'] = drupal_get_query_array($options['query']);
 //   }
 //   if (isset($alter['alias'])) {
 //     // Alias is a boolean field, so no token.
 //     $options['alias'] = $alter['alias'];
 //   }
 //   if (isset($alter['fragment'])) {
 //     $options['fragment'] = strtr($alter['fragment'], $tokens);
 //   }
 //   if (isset($alter['language'])) {
 //     $options['language'] = $alter['language'];
 //   }

 //   // If the url came from entity_uri(), pass along the required options.
 //   if (isset($alter['entity'])) {
 //     $options['entity'] = $alter['entity'];
 //   }
 //   if (isset($alter['entity_type'])) {
 //     $options['entity_type'] = $alter['entity_type'];
 //   }

 //   $value .= l($text, $path, $options);

 //   if (!empty($alter['suffix'])) {
 //     $value .= filter_xss_admin(strtr($alter['suffix'], $tokens));
 //   }

 //   return $value;
 // }

 // /**
 //  * Get the 'render' tokens to use for advanced rendering.
 //  *
 //  * This runs through all of the fields and arguments that
 //  * are available and gets their values. This will then be
 //  * used in one giant str_replace().
 //  */
 // function get_render_tokens($item) {
 //   $tokens = array();
 //   if (!empty($this->view->build_info['substitutions'])) {
 //     $tokens = $this->view->build_info['substitutions'];
 //   }
 //   $count = 0;
 //   foreach ($this->view->display_handler->get_handlers('argument') as $arg => $handler) {
 //     $token = '%' . ++$count;
 //     if (!isset($tokens[$token])) {
 //       $tokens[$token] = '';
 //     }

 //     // Use strip tags as there should never be HTML in the path.
 //     // However, we need to preserve special characters like " that
 //     // were removed by check_plain().
 //     $tokens['!' . $count] = isset($this->view->args[$count - 1]) ? strip_tags(html_entity_decode($this->view->args[$count - 1])) : '';
 //   }

 //   // Now add replacements for our fields.
 //   foreach ($this->view->display_handler->get_handlers('field') as $field => $handler) {
 //     if (isset($handler->last_render)) {
 //       $tokens["[$field]"] = $handler->last_render;
 //     }
 //     else {
 //       $tokens["[$field]"] = '';
 //     }
 //     $this->add_self_tokens($tokens, $item);

 //     // We only use fields up to (and including) this one.
 //     if ($field == $this->options['id']) {
 //       break;
 //     }
 //   }

 //   $this->last_tokens = $tokens;
 //   return $tokens;
 // }

 // /**
 //  * Add any special tokens this field might use for itself.
 //  *
 //  * This method is intended to be overridden by items that generate
 //  * fields as a list. For example, the field that displays all terms
 //  * on a node might have tokens for the tid and the term.
 //  *
 //  * By convention, tokens should follow the format of [token-subtoken]
 //  * where token is the field ID and subtoken is the field. If the
 //  * field ID is terms, then the tokens might be [terms-tid] and [terms-name].
 //  */
 // function add_self_tokens(&$tokens, $item) { }

 // /**
 //  * Document any special tokens this field might use for itself.
 //  *
 //  * @see add_self_tokens() for details.
 //  */
 // function document_self_tokens(&$tokens) { }

 // /**
 //  * Call out to the theme() function, which probably just calls render() but
 //  * allows sites to override output fairly easily.
 //  */
 // function theme($values) {
 //   return theme($this->theme_functions(),
 //     array(
 //       'view' => $this->view,
 //       'field' => $this,
 //       'row' => $values
 //     ));
 // }
}

/**
 * @}
 */
