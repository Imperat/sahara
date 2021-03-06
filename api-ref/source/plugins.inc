.. -*- rst -*-

=======
Plugins
=======

A plugin object defines the Hadoop or Spark version that it can
install and which configurations can be set for the cluster.


Show plugin details
===================

.. rest_method::  GET /v1.1/{tenant_id}/plugins/{plugin_name}

Shows details for a plugin.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: url_tenant_id
   - plugin_name: plugin_name


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - versions: versions
   - title: title
   - description: description
   - name: name



Response Example
----------------

.. literalinclude:: samples/plugins/plugin-show-response.json
   :language: javascript




List plugins
============

.. rest_method::  GET /v1.1/{tenant_id}/plugins

Lists all registered plugins.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: url_tenant_id



Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - title: title
   - versions: versions
   - plugins: plugins
   - description: description
   - name: name



Response Example
----------------

.. literalinclude:: samples/plugins/plugins-list-response.json
   :language: javascript




Show plugin version details
===========================

.. rest_method::  GET /v1.1/{tenant_id}/plugins/{plugin_name}/{version}

Shows details for a plugin version.


Normal response codes: 200
Error response codes:


Request
-------

.. rest_parameters:: parameters.yaml

   - tenant_id: url_tenant_id
   - plugin_name: plugin_name
   - version: version


Response Parameters
-------------------

.. rest_parameters:: parameters.yaml

   - versions: versions
   - title: title
   - description: description
   - name: name



Response Example
----------------

.. literalinclude:: samples/plugins/plugin-version-show-response.json
   :language: javascript



