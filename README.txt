SPARQL Views module
-------------------
By Lin Clark, lin-clark.com

This module adds:
- A query plugin for Views to query remote SPARQL endpoints, RDF files, and
  RDFa on Web pages.
- An entity type, sparql_views_entity, that is used to maintain an internal
  representation of the resource/predicate relationship. Bundles of this entity
  can be created either in code or through Field UI and provide the fields for
  manipulation with Views. The RDF mapping for the fields in the bundle is what
  is used to construct the query.
  
DEPENDENCIES
------------
This module depends upon:
- Entity API ('entity') for the sparql_views_entity functionality
- SPARQL ('sparql') for the SPARQL query API and SPARQL endpoint registry.

Optionally, the following modules may also be used:
- RDF UI ('rdfui', part of the 'rdf' contrib package) allows you to create
  mappings for bundles created using the Field UI

HONOR ROLL
----------
Thank you to:
- Remon Georgy (http://drupal.org/user/143827) for the idea to use an internal
  representation of the remote resources.
- Matthias 'netsensei' Vandermaesen (http://drupal.org/user/350460) for patches
  to the original SPARQL Views and brainstorming.
- Laura 'laura s' Scott (http://drupal.org/user/18973) for UI help on the
  Drupal 6 version.
- Google Summer of Code and Drupal's GSOC organizing team for initial support.
- Mark Birbeck (http://drupal.org/user/101283) for testing and bug reporting.
- Everyone who contributed ideas and suggestions in the issue queue and at
  Drupal events.