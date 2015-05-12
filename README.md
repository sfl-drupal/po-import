Automatically import po files
=============================

This modules provides a Drush command to automatically import the po files found in the profile directories.

Installation
------------

Drush searches for commandfiles in the following location:

* /path/to/drush/commands folder
* system-wide drush commands folder, e.g. /usr/share/drush/commands
* .drush folder in $HOME folder.
* sites/all/drush in the current Drupal installation
* all enabled modules folders in the current Drupal installation


Usage
-----

Minimum bootstrap config: DRUSH_BOOTSTRAP_DRUPAL_LOGIN. See `drush topic docs-bootstrap`.

Arguments:

 langcode                                  The langcode of the language in which the strings will be imported.

Options:

 --custom-only                             Import only custom modules translations. 

 --replace                                 Replace existing translations.
