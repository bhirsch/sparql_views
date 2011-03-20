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
        $entity_info = entity_get_info('sparql_views_resource');
        if(isset($entity_info)) {
          foreach($entity_info['bundles'] as $bundle_type => $bundle) {
            $rdf_mapping = $bundle['rdf_mapping'];
            $group = $bundle_type;  
            $new_fields = array();
            $new_fields[$bundle_type] = array(
              'title' => t('URI'),
              'help' => isset($rdf_mapping['rdftype']) ? t('RDF type: %type', array('%type' => $rdf_mapping['rdftype'])) : 'RDF resource',
              'group' => t($group),
              'field' => array(
                'handler' => 'sparql_views_handler_field_subject',
                'rdf_mapping' => isset($rdf_mapping['rdftype']) ? $rdf_mapping['rdftype'] : NULL,
              ),
            );
            foreach ($rdf_mapping as $field_name => $field ) {
              if($field_name == 'rdftype')
                continue;
              $new_field = array(
                'title' => t($field_name),
                'help' => t('RDF mapping: %rdf-mapping', array('%rdf-mapping' => implode(', ', $field['predicates']))),
                'group' => t($group),
                'field' => array(
                  'handler' => 'sparql_views_handler_field',
                  'rdf_mapping' => $field['predicates'],
                  'subject' => $bundle_type,
                ),
                'relationship' => array(
                  'help' => t('The last comment of a node.'),
                  'group' => t($group),
                  'base' => 'sparql_views',
                  'base field' => $field_name,
                  'handler' => 'sparql_views_handler_relationship',
                  'label' => t('Test Field'),
                ),
                'filter' => array(
                  'help' => t('Compare values.'),
                  'group' => t($group),
                  'base' => 'sparql_views',
                  'base field' => $field_name,
                  'handler' => 'sparql_views_handler_filter_field_value',
                  'label' => t('Test Field'),
                ),
              );
             
              $new_fields[$bundle_type.'_'.$field_name] = $new_field;
              $new_fields[$bundle_type.'_'.$field_name . '_language']['filter'] = array(
                'title' => t($field_name . ' language'),
                  'help' => t('Choose the language for return values.'),
                  'group' => t($group),
                  'base' => 'sparql_views',
                  'base field' => $bundle_type.'_'.$field_name,
                  'handler' => 'sparql_views_handler_filter_language',
                  'label' => t('Language'),
                );
             // $new_fields[$field_name.'_'.$bundle_type.'_'.$field_name.'_relationship'] = $new_relationship;
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