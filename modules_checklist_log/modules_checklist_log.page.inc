<?php

/**
 * @file
 * modules_checklist_log.page.inc.
 */

/**
 * Builds content of the page Modules Checklist Log.
 *
 * @return array
 */
function modules_checklist_log_page() {
  return array(
    'content' => array(
      '#markup' => views_embed_view('modules_checklist_log'),
    ),
  );
}
