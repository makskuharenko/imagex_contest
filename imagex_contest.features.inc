<?php
/**
 * @file
 * imagex_contest.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function imagex_contest_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "panelizer" && $api == "panelizer") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function imagex_contest_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function imagex_contest_node_info() {
  $items = array(
    'contest' => array(
      'name' => t('Contest'),
      'base' => 'node_content',
      'description' => t('Use <em>contest</em> to create a new community driven contest.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'contest_entry' => array(
      'name' => t('Contest Entry'),
      'base' => 'node_content',
      'description' => t('Use <em>contest entry</em> to submit an entry to an existing contest.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );

  features_alter_code('node', $items);

  return $items;
}
