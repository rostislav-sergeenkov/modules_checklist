<?php

/**
 * @file.
 * modules_checklist_log.admin.inc.
 */

/**
 * Builds settings form for Modules Checklist log module.
 */
function modules_checklist_settings_form() {
  $modules_data = system_rebuild_module_data();
  $config_path = conf_path() . '/settings.php';
  $check = modules_checklist_status_check($modules_data, $config_path);
  $required_modules = variable_get('modules_checklist_required_modules');
  $optional_modules = variable_get('modules_checklist_optional_modules');

  $module_options = array();
  $default_modules = array();

  foreach ($modules_data as $module_machine_name => $module) {
    $status = modules_checklist_log_get_module_status($module_machine_name);

    $module_options[$module_machine_name] = array(
      'enabled' => $module->status ?
        '<span class="enabled">' . t('enabled') . '</span>' : '<span class="disabled">' . t('disabled') . '</span>',
      'status' => '<span class="module-' . modules_checklist_log_get_module_status_label($status, FALSE) . '">' . modules_checklist_log_get_module_status_label($status) . '</span>',
      'name' => '<strong>' . $module->info['name'] . '</strong> [' . $module_machine_name . ']',
    );
    // @todo think how to parallel logic between required and optional modules. How to deal with optional modules.
    $default_modules[$module_machine_name] = (int) (is_array($required_modules) && in_array($module_machine_name, $required_modules));
  }

  if ($check['status'] == 'status') {
    $form['modules_checklist_status_check'] = array(
      '#markup' => '<div class="messages ' . $check['status'] . '">' . $check['message'] . '</div>',
    );
  }

  $form['check_all_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Check all enabled modules'),
    '#default_value' => 0,
  );

  $form['modules_checklist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available modules'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  $form['modules_checklist']['modules'] = array(
    '#type' => 'tableselect',
    '#header' => array(
      'enabled' => t('Enabled / Disabled'),
      'status' => t('Configuration Status'),
      'name' => t('Module Name'),
    ),
    '#options' => $module_options,
    '#default_value' => $default_modules,
  );

  $form['generate_required'] = array(
    '#type' => 'submit',
    '#name' => 'generate_required',
    '#value' => t('!button list of required modules',
      array('!button' => t(MODULE_CHECKLIST_GENERATE_BUTTON_TEXT))),
    '#submit' => array('modules_checklist_settings_form_generate_config'),
  );

  $form['generate_optional'] = array(
    '#type' => 'submit',
    '#name' => 'generate_optional',
    '#value' => t('!button list of optional modules',
      array('!button' => t(MODULE_CHECKLIST_GENERATE_BUTTON_TEXT))),
    '#submit' => array('modules_checklist_settings_form_generate_config'),
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'modules_checklist') . '/modules_checklist.css';
  $form['#attached']['js'][] = drupal_get_path('module', 'modules_checklist') . '/modules_checklist.js';

  return system_settings_form($form);
}

/**
 * Submit handler for the "Generate" button of modules_checklist_settings_form().
 */
function modules_checklist_settings_form_generate_config($form, &$form_state) {
  if ($form_state['triggering_element']['#name'] == 'generate_required') {
    $flag = 'required';
  }
  elseif ($form_state['triggering_element']['#name'] == 'generate_optional') {
    $flag = 'optional';
  }
  else {
    $flag = '';
  }

  $config = modules_checklist_get_modules_config_content($form_state['values']['modules_checklist']['modules'], $flag);
  drupal_set_message($config, 'status', FALSE);
}

/**
 * Returns config content ready to print of the screen.
 *
 * @param array $modules
 * @param string $flag
 *
 * @return string
 */
function modules_checklist_get_modules_config_content($modules, $flag) {
  $output = '';

  if (!empty($flag)) {
    $config_path = conf_path() . '/settings.php';
    $output = '<strong>// ' . t('Modules Checklist configuration. Copy the code below and paste it into !file file.', array('!file' => $config_path)) . '</strong><br/>';
    $output .= '$conf[' . "'modules_checklist_" . $flag . "_modules'" . '] = array(<br/>';
    $checked_modules = modules_checklist_get_checked_modules($modules);

    foreach ($checked_modules as $module_machine_name => $module_name) {
      $output .= '&#160;&#160;// "' . $module_name . '".<br/>';
      $output .= "&#160;&#160;'" . $module_machine_name . "',<br/>";
    }

    $output .= ');';
  }

  return $output;
}

/**
 * Returns list of selected modules that should be included in config.
 *
 * @param array $modules
 *
 * @return array
 */
function modules_checklist_get_checked_modules($modules) {
  $module_list = array();
  $modules_data = system_rebuild_module_data();

  foreach ($modules as $module_machine_name => $checked) {
    if (!empty($checked)) {
      $module_list[$module_machine_name] = $modules_data[$module_machine_name]->info['name'];
    }
  }

  return $module_list;
}
