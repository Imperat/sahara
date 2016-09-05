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

Upload image to Glance
----------------------
If you have image in glance, please, skip this step. If you haven't, firstly you should build an image
via `sahara-image-elements` with command:

.. code:: bash

    tox -e sahara-image-create -p vanilla -i ubuntu


and upload an image to glance:

.. code:: bash

   (openstack) image create --file vanilla-ubuntu-latest --project demo --disk-format qcow2 vanilla-ubuntu

Registering an image
--------------------
You must register image in Sahara. By registering an image you should set username and for convenience
description (optionally). 

.. code:: bash

    (openstack) dataprocessing image register vanilla-ubuntu --username Ubuntu --description "My first steps in Openstack Sahara"

::

    Note! Username isn't a username that you want to acess to instances. 
    This is username will be used by Sahara to configure clusters. For Ubuntu images
    this is 'ubuntu', 'fedora' for fedora images, 'cloud-user' for CentOS 6.x images
    and 'centos' for CentOS 7.x images.

You will add plugins tags to image. Every sahara plugin can start cluster deploying only if an image has according tag.
In this user guide we run simple vanilla cluster, that's why let add to image 'vanilla 2.7.1' tag with the following command:

.. code:: bash

   (openstack) dataprocessing image tags add vanilla-ubuntu --tag vanilla 2.7.1


Also you can add other any tags for you convenience. For example:

.. code:: bash

    (openstack) dataprocessing image tags add vanilla-ubuntu --tag "ubuntu 16.04"

Create Node Group Template
--------------------------

.. code:: bash

   (openstack) dataprocessing node group template create --name ml-master --plugin vanilla --plugin-version 2.7.1 --processes namenode hiveserver historyserver oozie resourcemanager --flavor m1.small

Create a Cluster Template
-------------------------

.. code:: bash

   dataprocessing cluster template create --name ml-cl-tmpl --node-groups ml-master:1

Launching a Cluster
-------------------

.. code:: bash

   dataprocessing cluster create --name ml-cluster --cluster-template ml-tmpl --image liberty-vanilla

You will wait several minutes for launching and configuring instances while cluster state isn't 'Active'.


Congrutulations! You have first own hadoop cluster in openstack cloud.

Scaling a Cluster
-----------------

.. code:: bash

   dataprocessing cluster scale --name ml-cluster --node-groups ml-master:2

Elastic Data Processing (EDP)
-----------------------------
Also about a run jobs.
