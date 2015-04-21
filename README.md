Automatically import po files
=============================

This modules provides a Drush command to automatically import the po files found in the profile directories.

Usage
-----

Minimum bootstrap config: DRUSH_BOOTSTRAP_DRUPAL_LOGIN. See `drush topic docs-bootstrap`.

Arguments:

 langcode                                  The langcode of the language in which the strings will be imported.

Options:

 --custom-only                             Import only custom modules translations. 

 --replace                                 Replace existing translations.
