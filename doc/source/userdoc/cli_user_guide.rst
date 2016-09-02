========================================
Sahara (Data Processing) CLI User Guide
========================================

This guide assumes that you already have the sahara service.
Don't forget to make sure that sahara is registered in Keystone.
If you requre assistance with that, please, see the installation
guide.

Launching a cluster via Sahara CLI commands
-------------------------------------------
This simple steps provide user to create sahara hadoop cluster
via Sahara (Data Processing) CLI commands.

Upload image to glance
----------------------

Registering an image
--------------------
.. code:: bash

    (openstack) dataprocessing image register liberty_vanilla --username Ubuntu --description "Writing docs to CLI"

::
    Note! Username isn't a username that you want to acess to instances. This is username will be used by
    Sahara to confugure clusters. For Ubuntu images this is 'ubuntu', 'fedora' for fedora images, 'cloud-user' for
    CentOS 6.x images and 'centos' for CentOS 7.x images.

You will add plugins tags to image. Every sahara plugin can start cluster deploying only if an image has according tag.
In this userguide we will run simple vanilla cluster, that's why let add to image 'vanilla 2.7.1' tag with the folloving
command:

.. code:: bash
   (openstack) dataprocessing image tags add liberty_vanilla --tag vanilla 2.7.1


Create Node Group Template
--------------------------
.. code:: bash
   (openstack) dataprocessing node group template create --name ml-master --plugin vanilla --plugin-version 2.7.1 --processes namenode hiveserver historyserver oozie resourcemanager --flavor m1.small
Create a Cluster Template
-------------------------
.. code:: bash
   dataprocessing cluster template create --name ml-cl-tmpl --node-groups ml-master:1
Launching a Cluster
------------------
.. code:: bash
   dataprocessing cluster create --name ml-cluster --cluster-template ml-tmpl --image liberty-vanilla

Congrutulations!
Scaling a Cluster
-----------------
.. code:: bash
   dataprocessing cluster scale --name ml-cluster --node-groups ml-master:2
Elastic Data Processing (EDP)
-----------------------------
Also about a run jobs.

