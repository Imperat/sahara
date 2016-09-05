========================================
Sahara (Data Processing) CLI User Guide
========================================

This guide assumes that you already have the sahara service.
Don't forget to make sure that sahara is registered in Keystone.
If you requre assistance with that, please, see the installation
guide.

Launching a cluster via Sahara CLI commands
===========================================
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
In this step you need create two Node Group templates. Instances in cluster can be differentiated by
assignment, but alike instances can be configured in common. By node group template creation you need
set name, name of plugin, version of plugin, flavor and list of node processes.
1. Let's create `master` node group template:

.. code:: bash

   (openstack) dataprocessing node group template create --name ml-master --plugin vanilla --plugin-version 2.7.1 --processes namenode hiveserver historyserver oozie resourcemanager --flavor m1.small

2. And 'worker' node group template:

.. code:: bash

   (openstack) dataprocessing node group template create --name worker --plugin vanilla --plugin-version 2.7.1 --processes --flavor m1.small

Create a Cluster Template
-------------------------
Let's create a cluster template for our cluster. Cluster template can contain only basically information: name, name of used node-groups and count of instances per every node groups. In folloving
command we create simple cluster template with own node groups. Our cluster must consist of one instance of master node group and three instances from worker node groups.


.. code:: bash

   (openstack) dataprocessing cluster template create --name ml-cl-tmpl --node-groups ml-master:1

Launching a Cluster
-------------------

.. code:: bash

   (openstack) dataprocessing cluster create --name ml-cluster --cluster-template ml-tmpl --image ubuntu-vanilla

You will wait several minutes for launching and configuring instances while cluster state isn't 'Active'.


Congrutulations! You have first own Hadoop cluster in Openstack cloud.

Scaling a Cluster
-----------------
If you want scale (increase or decrease count of instances in cluster), you can use simple following command:

.. code:: bash

   (openstack) dataprocessing cluster scale --name ml-cluster --node-groups worker:6

Also you can add new node group to cluster by using this command:

   (openstack) dataprocessing cluster scale --name ml-cluster --node-groups core-worker:3


Elastic Data Processing (EDP)
=============================
Sahara has mechanism to run different jobs via you clusters.

Job Binaries
------------
Job Binaries are where you define/upload the source code (mains and libraries) for your job.
Firstly you need download you binary file or script to swift file system.

And register you file in Sahara by command:

.. code:: bash

    (openstack) dataprocessing job binary create --url "swift://kefal/jefal.txt" --username username --password password --description "My first job binary"


Data Sources
------------
Data Sources are where the input and output from your jobs are housed.
You can create Data Sources which related to Swift or HDFS. You need necessary set type of Data Source (swift, hdfs), name and url. For the next two commands let's create input and output data sources in swift:

.. code:: bash

   (openstack) dataprocessing data source create --type swift --username admin --password admin --url "swift://keal/input.txt" input

   (openstack) dataprocessing data source create --type swift --username admin --password admin --url "swift://keal/output.txt" input

If you want to create data sources in hdfs, use hdfs-correctly urls:

.. code:: bash

   (openstack) dataprocessing data source create --type hdfs --url "hdfs://keal/kefal.txt" input

   (openstack) dataprocessing data source create --type hdfs --url "hdfs://keal/output.txt" output


Job Templates (Jobs in API)
---------------------------






 

