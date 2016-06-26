<?php

/**
 * @file
 * modules_checklist_log.page.inc.
 */

/**
 * Builds Modules Checklist log page.
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
