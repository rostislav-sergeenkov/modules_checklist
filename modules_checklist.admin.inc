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

  // @todo check if variable is present in config. Otherwise show message and display it on all the pages. Create function modules_checklist_status_check().
  $form['modules_checklist_status_check'] = array(
    '#markup' => '<div class="messages warning">' . t('Save Brand and add entitlements to see entitlements data.') . '</div>',
  );

  $form['modules_checklist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available modules'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  foreach ($modules_data as $module_machine_name => $module) {
    $form['modules_checklist'][$module_machine_name] = array(
      '#type' => 'checkbox',
      '#title' => $module->info['name'],
      // @todo specify default value based on logic: if the module is present in the config - add, otherwise skip.
      // '#default_value' => 0,
    );
  }

  $form['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Generate'),
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
  $output = '<strong>// ' . t('Copy the code below and paste into !file.', array('!file' => $config_path)) . '</strong><br/>';
  $output .= '$conf[' . "'modules_checklist_required_modules'" . '] = array(<br/>';
  $checked_modules = modules_checklist_get_checked_modules($modules);

  foreach ($checked_modules as $module_machine_name => $module_name) {
    $output .= '&#160;&#160;// "' . $module_name . '".<br/>';
    $output .= '&#160;&#160;' . $module_machine_name . ',<br/>';
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
