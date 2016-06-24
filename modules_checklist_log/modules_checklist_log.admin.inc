<?php

/**
 * @file.
 * modules_checklist_log.admin.inc.
 */

/**
 * Builds settings form for Modules Checklist Log module.
 */
function modules_checklist_log_settings_form() {
  $form['modules_checklist_log_rotation_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable log rotation'),
    '#description' => t('Removes the log entries from the database. Relies on cron run.'),
    '#default_value' => variable_get('modules_checklist_log_rotation_enabled', MODULES_CHECKLIST_LOG_DEFAULT_ROTATION_STATUS),
  );

  $form['modules_checklist_log_rotation_period'] = array(
    '#type' => 'textfield',
    '#title' => t('How long should log entries be kept?'),
    '#description' => t('How many days to keep log entries.'),
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => variable_get('modules_checklist_log_rotation_period', MODULES_CHECKLIST_LOG_DEFAULT_ROTATION_PERIOD),
    '#states' => array(
      'visible' => array(
        ':input[name=modules_checklist_log_rotation_enabled]' => array('checked' => TRUE),
      ),
    ),
  );

  return system_settings_form($form);
}
