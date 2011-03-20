<?php
// $Id$

/**
 * @file
 * SPARQL Views type editing UI.
 */

/**
 * UI controller.
 */
class SparqlViewsResourceTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage SPARQL Views resource types, including fields.';
    return $items;
  }
}

/**
 * Generates the message type editing form.
 */
function sparql_views_resource_type_form($form, &$form_state, $resource_type, $op = 'edit') {
  if ($op == 'clone') {
    $resource_type->label .= ' (cloned)';
    $resource_type->name .= '_clone';
  }

  $form['description'] = array(
    '#title' => t('Description'),
    '#type' => 'textfield',
    '#default_value' => $resource_type->description,
    '#description' => t('The human-readable description of this message type.'),
    '#required' => TRUE,
  );
  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($resource_type->name) ? $resource_type->name : '',
    '#disabled' => entity_has_status('sparql_views_resource_type', $resource_type, ENTITY_IN_CODE),
    '#machine_name' => array(
      'exists' => 'sparql_views_resource_type_load',
      'source' => array('description'),
    ),
    '#description' => t('A unique machine-readable name for this message type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  field_attach_form('sparql_views_resource_type', $resource_type, $form, $form_state);

  $form['argument_keys'] = array(
    '#title' => t('Replacement tokens'),
    '#type' => 'textfield',
    '#default_value' => implode(', ', $resource_type->argument_keys),
    '#description' => t('A comma-separated list of replacement tokens, e.g. %title or !url, of which the message text makes use of. Each replacement token has to start with one of the special characters "@", "%" or "!". This character controls the sanitization method used, analogously to the <a href="!link">t()</a> function.', array('!link' => 'http://api.drupal.org/api/drupal/includes--bootstrap.inc/function/t/7')),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save message type'),
    '#weight' => 40,
  );

  if (!entity_has_status('sparql_views_resource_type', $resource_type, ENTITY_IN_CODE) && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete message type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('sparql_views_resource_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Validation callback.
 */
function sparql_views_resource_type_form_validate($form, &$form_state) {
  entity_form_field_validate('sparql_views_resource_type', $form, $form_state);
}

/**
 * Form API submit callback for the type form.
 */
function sparql_views_resource_type_form_submit(&$form, &$form_state) {
  $resource_type = entity_ui_form_submit_build_entity($form, $form_state);
  $resource_type->argument_keys = array_map('trim', explode(',', $resource_type->argument_keys));
  // Save and go back.
  $resource_type->save();
  $form_state['redirect'] = 'admin/structure/messages';
}

/**
 * Form API submit callback for the delete button.
 */
function sparql_views_resource_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/sparql-views/manage/' . $form_state['sparql_views_resource_type']->name . '/delete';
}
