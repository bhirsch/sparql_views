<?php
// $Id$
function sparql_views_views_data() {
  $data['sparql_views']['table']['group']  = t('SPARQL Views');

  $data['sparql_views']['table']['base'] = array(
    'field' =>'vsid',
    'title' => t('SPARQL Views'),
    'query class' => 'sparql_views_query',
    'help' => t('Views SPARQL query builder'),
  );
  
  return $data;
}

function sparql_views_views_data_alter(&$data) {
  $base_tables = array();
  foreach($data as $key => $value) {
    // @TODO add conditional on entity types to expose them in SPARQL Views as
    // well. This will allow people to use the default types to query other
    // Drupal sites.
    if(isset($value['table']['group']) && $value['table']['group'] == 'SPARQL Views') {
        $entity_info = entity_get_info('sparql_views_entity');
        if(isset($entity_info)) {
          foreach($entity_info['bundles'] as $bn_key => $bn_value) {
            $bn_rdf_mapping = $bn_value['rdf_mapping'];
            $new_fields = array();
            foreach ($bn_rdf_mapping as $key => $field ) {
              if($key == 'rdftype')
                continue;
              $group = $bn_key;  
              $new_field = array(
                'title' => t($key),
                'help' => t('RDF mapping: %rdf-mapping', array('%rdf-mapping' => implode(', ', $bn_rdf_mapping[$key]['predicates']))),
                'group' => t($group),
                'field' => array(
                  'handler' => 'sparql_views_handler_field',
                  'rdf_mapping' => $bn_rdf_mapping[$key],
                ),
                'relationship' => array(
                  'help' => t('The last comment of a node.'),
                  'group' => t($group),
                  'base' => 'sparql_views',
                  'base field' => $key,
                  'handler' => 'sparql_views_handler_relationship',
                  'label' => t('Test Field'),
                ),
              );
             
              $new_fields[$bn_key.'_'.$key] = $new_field;
             // $new_fields[$key.'_'.$bn_key.'_'.$key.'_relationship'] = $new_relationship;
            }
            $data['sparql_views'] = array_merge($data['sparql_views'], $new_fields);  
          }
      }
    }
  }
}

/**
 * Implementation of hook_views_plugins().
 */
function sparql_views_views_plugins() {
  return array(
    'query' => array(
      'sparql_views_query' => array(
        'title' => t('SPARQL Query'),
        'help' => t('SPARQL Query'),
        'handler' => 'sparql_views_plugin_query_sparql'
      ),
    ),
  );
}

/**
 * Implements hook_field_views_data().
 *
 * In addition to the default field information we add the relationship for
 * views to connect back to the base table.
 */
function sparql_views_field_views_data_alter($field) {
  /*$data = field_views_field_default_views_data($field);
  foreach ($data as $table_name => $table_data) {
    foreach ($table_data as $field_name => $field_data) {
        $data[$table_name][$field_name]['relationship'] = array(
          'handler' => 'sparql_views_handler_relationship',
          'base' => 'sparql_views_entity',
          'base field' => 'pid',
          'label' => t('term from !field_name', array('!field_name' => $field['field_name'])),
        );
    }
  }
  return $data;*/
}