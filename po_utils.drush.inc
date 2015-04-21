<?php

/**
 * Implements hook_drush_command().
 */
function po_utils_drush_command() {
  $items['po-import'] = array(
    'description' => dt('Import all translation files for a given language.'),
    'arguments' => array(
      'langcode' => dt('The langcode of the language in which the strings will be imported.'),
    ),
    'options' => array(
      'replace' => array(
        'description' => dt('Replace existing translations.'),
        'value' => 'optional',
      ),
      'custom-only' => array(
        'description' => dt('Import only custom modules translations.'),
        'value' => 'optional',
      ),
    ),
    'example' => array(
      'drush po-import fr --replace' => 'Import all French translations and replace existing ones.'
    ),
  );
  return $items;
}


/**
 * Implements drush_COMMANDFILE_COMMANDNAME().
 */
function drush_po_utils_po_import() {
  $args = func_get_args();
  if (count($args) < 1) {
    drush_set_error(dt('Usage: drush po-import <langcode> [--replace]'));
    return;
  }

  // Get arguments and options
  $langcode = $args[0];
  $replace = drush_get_option('replace');
  $customOnly = drush_get_option('custom-only');
  $mode = isset($replace) ? LOCALE_IMPORT_OVERWRITE : LOCALE_IMPORT_KEEP;

  // Get all .po files
  $path  = $customOnly ? 'profiles/tatooine/modules/custom' : 'profiles/tatooine/modules';
  $directory = new RecursiveDirectoryIterator($path);
  $iterator = new RecursiveIteratorIterator($directory);
  $file_paths = array();
  foreach($iterator as $file) {
    if (substr($file, strrpos($file, '/') + 1) == $langcode . '.po') {
      $file_paths[] = $file->getPathName();
    }
  }

  // Add Drupal core translations
  if(!$customOnly) {
    $core_path = "translations/" . $langcode . ".po";
    if (file_exists($core_path)) {
      $file_paths[] = $core_path;
    }
  }

  // Display an error if no .po file is found
  if (empty($file_paths)) {
    drush_set_error(dt('No available .po file for this language.'));
  }

  // Import language files
  foreach ($file_paths as $file_path) {

    // Construct a fake file object
    $file = new stdClass();
    $file->uid = 1;
    $file->status = 0;
    $file->filename = trim(drupal_basename($file_path), '.');
    $file->uri = $file_path;

    // Now import strings
    if ($return = _locale_import_po($file, $langcode, $mode, 'default') == FALSE) {
      $variables = array('%filename' => $file->filename);
      drush_log(dt('The translation import of %filename failed.', $variables), 'error');
    }
  }
}

