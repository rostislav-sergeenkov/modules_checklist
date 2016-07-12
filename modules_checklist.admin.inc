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

  if ($check['status'] == 'status') {
    $form['modules_checklist_status_check'] = array(
      '#markup' => '<div class="messages ' . $check['status'] . '">' . $check['message'] . '</div>',
    );
  }

  $form['check_all'] = array(
    '#type' => 'radios',
    '#title' => t('Set all enabled modules as'),
    '#options' => array(
      'required' => t('required'),
      'optional' => t('optional'),
      'disabled' => t('disabled'),
    ),
    '#default_value' => 0,
  );

  $form['uncheck_disabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Uncheck/exclude all disabled modules'),
    '#default_value' => 0,
  );

  $form['modules_checklist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Available modules'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    '#theme' => 'modules_checklist_table',
  );

  foreach ($modules_data as $module_machine_name => $module) {
    $module_is_required = (int) (is_array($required_modules) && in_array($module_machine_name, $required_modules));
    $module_is_optional = (int) (is_array($optional_modules) && in_array($module_machine_name, $optional_modules));
    $module_is_disabled = (int) !$module_is_required && !$module_is_optional;

    $form['modules_checklist']['modules'][$module_machine_name]['required'] = array(
      '#type' => 'radio',
      '#default_value' => $module_is_required,
      '#attributes' => array(
        'data-module' => $module_machine_name,
        'data-status' => 'required',
        'data-checked' => $module_is_required,
        'data-enabled' => $module->status ? 'enabled' : 'disabled',
      ),
    );

    $form['modules_checklist']['modules'][$module_machine_name]['optional'] = array(
      '#type' => 'radio',
      '#default_value' => $module_is_optional,
      '#attributes' => array(
        'data-module' => $module_machine_name,
        'data-status' => 'optional',
        'data-checked' => $module_is_optional,
        'data-enabled' => $module->status ? 'enabled' : 'disabled',
      ),
    );

    $form['modules_checklist']['modules'][$module_machine_name]['disabled'] = array(
      '#type' => 'radio',
      '#default_value' => $module_is_disabled,
      '#attributes' => array(
        'data-module' => $module_machine_name,
        'data-status' => 'disabled',
        'data-checked' => $module_is_disabled,
        'data-enabled' => $module->status ? 'enabled' : 'disabled',
      ),
    );

    $form['modules_checklist']['modules'][$module_machine_name]['enabled'] = array(
      '#markup' => $module->status ?
        '<span class="enabled">' . t('enabled') . '</span>' : '<span class="disabled">' . t('disabled') . '</span>',
    );

    $form['modules_checklist']['modules'][$module_machine_name]['label'] = array(
      '#markup' => '<strong>' . $module->info['name'] . '</strong> [' . $module_machine_name . ']',
    );
  }

  $form['generate_required'] = array(
    '#type' => 'submit',
    '#value' => t(MODULE_CHECKLIST_GENERATE_BUTTON_TEXT),
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
  $messages = array(
    'required' => array(),
    'optional' => array(),
  );
  $required_modules = array();
  $optional_modules = array();
  $disabled_modules = array();

  foreach ($form_state['values']['modules_checklist']['modules'] as $module => $module_values) {
    foreach ($module_values as $key => $value) {
      if ($value === 'on') {
        if ($key == 'required') {
          $required_modules[] = $module;
        }
        elseif ($key == 'optional') {
          $optional_modules[] = $module;
        }
        elseif ($key == 'disabled') {
          $disabled_modules[] = $module;
        }
      }
    }
  }

  if (!empty($required_modules) || !empty($optional_modules)) {
    if (!empty($required_modules)) {
      $messages['required'] = $required_modules;
    }

    if (!empty($optional_modules)) {
      $messages['optional'] = $optional_modules;
    }
  }

  foreach ($messages as $type => $data) {
    $config = modules_checklist_get_modules_config_content($data, $type);
    drupal_set_message($config, 'status', FALSE);
  }
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
    $header = t('Modules Checklist: !flag modules. Copy the code below and paste it into !file file.',
      array('!file' => $config_path, '!flag' => $flag));
    $output = '<strong>// ' . $header . '</strong><br/>';
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

  foreach ($modules as $module_machine_name) {
    $module_list[$module_machine_name] = $modules_data[$module_machine_name]->info['name'];
  }

  return $module_list;
}

/**
 * Renders table on the Modules Checklist settings page.
 *
 * @return string
 */
function theme_modules_checklist_table($variables) {
  $modules = $variables['form']['modules'];
  $header = array(
    t('config: required'),
    t('config: optional'),
    t('config: disabled'),
    t('module status'),
    t('module'),
  );

  $rows = array();

  foreach ($modules as $module_machine_name => $module_options) {
    if (is_array($module_options)) {
      $module_elements = element_children($module_options);
      $row = array();

      foreach ($module_elements as $value) {
        if (is_string($value)) {
          $row[] = drupal_render($modules[$module_machine_name][$value]);
        }
      }

      $rows[] = $row;
    }
  }

  return theme('table',
    array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array(
        'id' => array('modules_checklist_table'),
      ),
    )
  );
}
