<?php

/**
 * @file
 * File modules_checklist_log.page.inc.
 */

/**
 * Builds Modules Checklist log page.
 *
 * @return array
 */
function modules_checklist_log_page() {
  $view_exists = views_get_view('modules_checklist_log');

  if (!$view_exists) {
    drupal_set_message(t('View "modules_checklist_log" cannot be loaded. Please !do "Modules Checklist log" module.',
      array('!do' => l(t('re-install'), 'admin/modules'))), 'error');
  }

  return array(
    'content' => array(
      '#markup' => $view_exists ?
        views_embed_view('modules_checklist_log') : '',
    ),
  );
}
