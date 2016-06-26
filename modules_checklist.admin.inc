<?php

/**
 * @file.
 * modules_checklist_log.admin.inc.
 */

/**
 * Builds settings form for Modules Checklist log module.
 */
function modules_checklist_settings_form() {
  $required_modules = variable_get('modules_checklist_required_modules');
  $modules_data = system_rebuild_module_data();
  $config_path = conf_path() . '/settings.php';
  $generate_button_text = 'Generate';
  $check = modules_checklist_status_check($modules_data, $config_path, $generate_button_text);

  $form['modules_checklist_status_check'] = array(
    '#markup' => '<div class="messages ' . $check['status'] . '">' . $check['message'] . '</div>',
  );

  $form['modules_checklist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available modules'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  foreach ($modules_data as $module_machine_name => $module) {
    $prefix = $module->status ?
      '<em class="enabled">' . t('enabled') . '</em>' : '<em class="disabled">' . t('disabled') . '</em>';

    $form['modules_checklist'][$module_machine_name] = array(
      '#type' => 'checkbox',
      '#title' => $prefix . ' <strong>' . $module->info['name'] . '</strong> [' . $module_machine_name . ']',
      '#default_value' => is_array($required_modules) && in_array($module_machine_name, $required_modules),
    );
  }

  $form['generate'] = array(
    '#type' => 'submit',
    '#value' => t($generate_button_text),
    '#submit' => array('modules_checklist_settings_form_generate_config'),
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'modules_checklist') . '/modules_checklist.css';

  return system_settings_form($form);
}

/**
 * Submit handler for the "Generate" button of modules_checklist_settings_form().
 */
function modules_checklist_settings_form_generate_config($form, &$form_state) {
  $config = modules_checklist_get_modules_config_content($form_state['values']['modules_checklist']);
  drupal_set_message($config);
}

/**
 * Returns config content ready to print of the screen.
 *
 * @param $modules
 *
 * @return string
 */
function modules_checklist_get_modules_config_content($modules) {
  $config_path = conf_path() . '/settings.php';
  $output = '<strong>// ' . t('Modules Checklist. Copy the code below and paste into !file file.', array('!file' => $config_path)) . '</strong><br/>';
  $output .= '$conf[' . "'modules_checklist_required_modules'" . '] = array(<br/>';
  $checked_modules = modules_checklist_get_checked_modules($modules);

  foreach ($checked_modules as $module_machine_name => $module_name) {
    $output .= '&#160;&#160;// "' . $module_name . '".<br/>';
    $output .= "&#160;&#160;'" . $module_machine_name . "',<br/>";
  }

  $output .= ');';

  return $output;
}

/**
 * Returns list of selected modules that should be included in config.
 *
 * @param $modules
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
