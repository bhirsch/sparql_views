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
 * Generates the resource type editing form.
 */
function sparql_views_resource_type_form($form, &$form_state, $resource_type, $op = 'edit') {
  if ($op == 'clone') {
    $resource_type->label .= ' (cloned)';
    $resource_type->name .= '_clone';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => isset($resource_type->label) ? $resource_type->label : '',
    '#description' => t('The human-readable label of this resource type.'),
    '#required' => TRUE,
  );
  // Machine-readable type name.
  $form['name'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($resource_type->name) ? $resource_type->name : '',
    '#disabled' => entity_has_status('sparql_views_resource_type', $resource_type, ENTITY_IN_CODE),
    '#machine_name' => array(
      'exists' => 'sparql_views_resource_type_load',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this resource type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  field_attach_form('sparql_views_resource_type', $resource_type, $form, $form_state);

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save resource type'),
    '#weight' => 40,
  );

  if (!entity_has_status('sparql_views_resource_type', $resource_type, ENTITY_IN_CODE) && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete resource type'),
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
  // Save and go back.
  $resource_type->save();
  $form_state['redirect'] = 'admin/structure/sparql-views';
}

/**
 * Form API submit callback for the delete button.
 */
function sparql_views_resource_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/sparql-views/manage/' . $form_state['sparql_views_resource_type']->name . '/delete';
}
