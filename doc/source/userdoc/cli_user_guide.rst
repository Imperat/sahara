========================================
Sahara (Data Processing) CLI User Guide
========================================

This guide assumes that you have the sahara service.
Don't forget to make sure that sahara is registered in Keystone.
If you require assistance with that, please see the installation guide.

Launching a cluster via Sahara CLI commands
===========================================
These simple steps provide user to create sahara hadoop cluster
via Sahara (Data Processing) CLI commands.

Upload image to Glance
----------------------
If you have image in glance, please, skip the step. If you haven't, firstly you should build an image
via `sahara-image-elements` with command:

.. code:: bash

    tox -e sahara-image-create -p vanilla -i ubuntu


and upload an image to glance:

.. code:: bash

   (openstack) image create --file vanilla-ubuntu-latest --project demo --disk-format qcow2 vanilla-ubuntu

Registering an image
--------------------
You have to register image in Sahara. By registering an image you should set username and for convenience
description (optionally). 

.. code:: bash

    (openstack) dataprocessing image register vanilla-ubuntu --username Ubuntu --description "My first steps in Openstack Sahara"

::

    Note! This username isn't a username which you use to acess to instances. 
    This username will be used by Sahara to configure clusters. For Ubuntu images
    this is 'ubuntu', 'fedora' for fedora images, 'cloud-user' for CentOS 6.x images
    and 'centos' for CentOS 7.x images.

You will add plugins tags to image. Every sahara plugin can start cluster deploying only if an image has relevant tag.
In this user guide we run simple vanilla cluster, that's why we add to image 'vanilla 2.7.1' tag with the following command:

.. code:: bash

   (openstack) dataprocessing image tags add vanilla-ubuntu --tag vanilla 2.7.1


Also you can add any other tags for your convenience. For instance:

.. code:: bash

    (openstack) dataprocessing image tags add vanilla-ubuntu --tag "ubuntu-16.04"

::

    Note! Image tags can't have whitespaces.

Create Node Group Template
--------------------------
In this step you need to create two Node Group templates. Instances in cluster may be differentiated by
assignment, but the same instances can be configured in common. You should 
set name, name of plugin, version of plugin, flavor, list of node processes and network by node group template creation.


1. Let's create `master` node group template:

.. code:: bash

   (openstack) dataprocessing node group template create --name ml-master --plugin vanilla --plugin-version 2.7.1 --processes namenode hiveserver historyserver oozie resourcemanager --flavor m1.small --floating-ip-pool a53f5e32-da44-437a-ae4d-c75a6cb05841

2. And 'worker' node group template:

.. code:: bash

   (openstack) dataprocessing node group template create --name worker --plugin vanilla --plugin-version 2.7.1 --processes datanode nodemanager --flavor m1.small --floating-ip-pool a53f5e32-da44-437a-ae4d-c75a6cb05841

::

    Note! To determine ip of network you can use following openstack command:


.. code:: bash

   (openstack) network list

Create a Cluster Template
-------------------------
Let's create a cluster template for our cluster. Cluster template may contain basic information only: name, name of needed node-groups and count of instances for every node groups. In folloving
command we create simple cluster template with our node groups. Our cluster must consist of the one instance of master node group and three instances of worker node groups.


.. code:: bash

   (openstack) dataprocessing cluster template create --name ml-cl-tmpl --node-groups ml-master-vanilla:1 ml-worker-vanilla:3

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

Also you may add new node group to cluster by using this command:

.. code:: bash

   (openstack) dataprocessing cluster scale --name ml-cluster --node-groups core-worker:3


Elastic Data Processing (EDP)
=============================
Sahara has mechanism to run different jobs in your clusters.

Job Binaries
------------
Job Binaries are where you define/upload the source code (mains and libraries) for your job.
Firstly you need download you binary file or script to swift file system.

And register you file in Sahara by command:

.. code:: bash

    (openstack) dataprocessing job binary create --url "swift://integration.sahara/hive.sql" --username username --password password --description "My first job binary" hive-binary


Data Sources
------------
Data Sources are where the input and output from your jobs are housed.
You can create Data Sources which are related to Swift or HDFS. You need to set type of Data Source (swift, hdfs), name and url. For the next two commands let's create input and output data sources in swift:

.. code:: bash

   (openstack) dataprocessing data source create --type swift --username admin --password admin --url "swift://integration.sahara/input.txt" input

   (openstack) dataprocessing data source create --type swift --username admin --password admin --url "swift://integration.sahara/output.txt" input

If you want to create data sources in hdfs, use hdfs-correctly urls:

.. code:: bash

   (openstack) dataprocessing data source create --type hdfs --url "hdfs://tmp/input.txt" input

   (openstack) dataprocessing data source create --type hdfs --url "hdfs://tmp/output.txt" output


Job Templates (Jobs in API)
---------------------------
In this step you need to create job template. Set a type of job template as `type` parameter. Set main library with name ob job binary which was created at previous step and set name of job template. Example of
command: 

.. code:: bash

    (openstack) dataprocessing job template create --type Hive --name hive-job-template --main hive-binary

Jobs (Job Executions in API)
----------------------------
This is the last step in our guide. In this step you need to launch you job. You need to pass as arguments name or ID of input/output data sources for job, name or ID of job template and name or ID of cluster which will be used for job start. For instance:

.. code:: bash

    (openstack) dataprocessing job execute --input input --output output  --job-template hive-job-template --cluster my-first-cluster

After waiting a few minutes check the file of output data source. It will contain output data of this job. Congratulations!

Launch commands with JSON
-------------------------
In CLI there is ability to launch all commands with json format. I need to describe arguments in json file and launch you
commands with ``--json`` argument. Example:

File example.json:


.. code:: javascript

    {
    "plugin_name": "vanilla",
    "hadoop_version": "2.7.1",
    "node_processes": [
        "namenode",
        "resourcemanager",
        "oozie",
        "historyserver"
    ],
    "name": "ml-master",
    "floating_ip_pool": "77e2c46d-9585-46a2-95f9-8721c302b257",
    "flavor_id": "3"
    }

And command:


.. code:: bash

    (openstack) dataprocessing node group template create --json example.json
