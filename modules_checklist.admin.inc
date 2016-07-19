<?php

/**
 * @file
 * File modules_checklist_log.admin.inc.
 */

/**
 * Builds settings form for Modules Checklist log module.
 */
function modules_checklist_settings_form($form, &$form_state) {
  $modules_data = system_rebuild_module_data();
  $required_modules = variable_get('modules_checklist_required_modules');
  $optional_modules = variable_get('modules_checklist_optional_modules');
  $notification_settings = variable_get('modules_checklist_notification', modules_checklist_get_default_notification_settings());
  $email_tokens = modules_checklist_get_email_tokens();

  if (!empty($form_state['storage']['config_content'])) {
    $form['modules_checklist_config_value'] = array(
      '#title' => t('Copy the code below and paste it into !file.',
        array('!file' => conf_path() . '/settings.php')),
      '#type' => 'textarea',
      '#rows' => 25,
      '#value' => $form_state['storage']['config_content'],
      '#attributes' => array(
        'class' => array('modules_checklist_config_value'),
      ),
      '#weight' => -100,
    );
  }
  else {
    $check = modules_checklist_status_check($modules_data);

    $form['modules_checklist_status_check'] = array(
      '#markup' => '<div class="messages ' . $check['status'] . '">' . $check['message'] . '</div>',
      '#weight' => -90,
    );
  }

  $form['modules_checklist_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Config generation'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['modules_checklist_config']['howto'] = array(
    '#title' => '<strong>' . t('How to set up the module') . '</strong>',
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['modules_checklist_config']['howto']['manual'] = array(
    '#theme' => 'item_list',
    '#items' => array(
      '<strong>' . t('Make sure you are able to modify !file for your Project.', array('!file' => conf_path() . '/settings.php')) . '</strong>',
      '<strong>' . t('Check modules you wish to track using "Configuration" form below. Modules can be required, optional or disabled.') . '</strong>',
      t('Required modules are important modules for the project. They must stay enabled all the time and added to $conf["modules_checklist_required_modules"].'),
      t('Optional or ignored modules can be disabled, enabled or absent. Module just ignores them. Optional modules should be added to to $conf["modules_checklist_optional_modules"]. If you aren\'t sure about the module just add it to the list of optional modules.'),
      t('Disabled modules are unwanted modules. In theory they should be removed from the project it this is possible or at least disabled. If there are no required or optional modules just set all modules as disabled.'),
      '<strong>' . t('Click "!button" button to generate code for $conf variables.', array('!button' => MODULES_CHECKLIST_GENERATE_BUTTON_TEXT)) . '</strong>',
      '<strong>' . t('Copy the generated code and paste it into !file to complete setup.', array('!file' => conf_path() . '/settings.php')) . '</strong>',
      '<strong>' . t('Module Checklist compares the list of enabled modules with the lists of modules in $conf. In case of any discrepancy with the list of required or disabled modules it displays error message on !page page.',
        array('!page' => l(t('Status report'), 'admin/reports/status'))) . '</strong>',
      '<strong>' . t('If "Modules Checklist log" is !enabled then you will be able !view and know who installed / enabled / disabled / unistalled the module.',
        array('!enabled' => l(t('enabled'), 'admin/modules'), '!view' => l(t('to browse the history'), 'admin/reports/modules_checklist_log'))) . '</strong>',
    ),
    '#type' => 'ol',
    '#attributes' => array(
      'class' => array(
        'modules_checklist_config_description',
      ),
    ),
    '#weight' => -80,
  );

  $form['modules_checklist_config']['check_all'] = array(
    '#type' => 'radios',
    '#title' => t('Set all enabled modules as'),
    '#options' => array(
      'required' => t('required'),
      'optional' => t('optional'),
      'disabled' => t('disabled'),
    ),
    '#default_value' => 0,
  );

  $form['modules_checklist_config']['uncheck_disabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Uncheck/exclude all disabled modules'),
    '#default_value' => 0,
  );

  $form['modules_checklist_config']['modules_checklist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Configuration helper'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    '#theme' => 'modules_checklist_table',
  );

  foreach ($modules_data as $module_machine_name => $module) {
    $module_is_required = (int) (is_array($required_modules) && in_array($module_machine_name, $required_modules));
    $module_is_optional = (int) (is_array($optional_modules) && in_array($module_machine_name, $optional_modules));
    $module_is_disabled = (int) !$module_is_required && !$module_is_optional;

    $form['modules_checklist_config']['modules_checklist']['modules'][$module_machine_name]['required'] = array(
      '#type' => 'radio',
      '#default_value' => $module_is_required,
      '#attributes' => array(
        'data-module' => $module_machine_name,
        'data-status' => 'required',
        'data-checked' => $module_is_required,
        'data-enabled' => $module->status ? 'enabled' : 'disabled',
      ),
    );

    $form['modules_checklist_config']['modules_checklist']['modules'][$module_machine_name]['optional'] = array(
      '#type' => 'radio',
      '#default_value' => $module_is_optional,
      '#attributes' => array(
        'data-module' => $module_machine_name,
        'data-status' => 'optional',
        'data-checked' => $module_is_optional,
        'data-enabled' => $module->status ? 'enabled' : 'disabled',
      ),
    );

    $form['modules_checklist_config']['modules_checklist']['modules'][$module_machine_name]['disabled'] = array(
      '#type' => 'radio',
      '#default_value' => $module_is_disabled,
      '#attributes' => array(
        'data-module' => $module_machine_name,
        'data-status' => 'disabled',
        'data-checked' => $module_is_disabled,
        'data-enabled' => $module->status ? 'enabled' : 'disabled',
      ),
    );

    $form['modules_checklist_config']['modules_checklist']['modules'][$module_machine_name]['enabled'] = array(
      '#markup' => $module->status ?
        '<span class="enabled">' . t('enabled') . '</span>' : '<span class="disabled">' . t('disabled') . '</span>',
    );

    $form['modules_checklist_config']['modules_checklist']['modules'][$module_machine_name]['label'] = array(
      '#markup' => '<strong>' . $module->info['name'] . '</strong> [' . $module_machine_name . ']',
    );
  }

  $form['modules_checklist_config']['modules_checklist_generate_config'] = array(
    '#type' => 'submit',
    '#value' => t(MODULES_CHECKLIST_GENERATE_BUTTON_TEXT),
    '#submit' => array('modules_checklist_settings_form_generate_config'),
  );

  $form['modules_checklist_config']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#submit' => array('modules_checklist_settings_form_reset'),
  );

  $form['modules_checklist_notification'] = array(
    '#title' => t('Email notification'),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
  );

  $form['modules_checklist_notification']['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable email notification for the required modules'),
    '#description' => t('Enables email notification triggering by any action (disabling, uninstallation, enabling, installation) of any required module.'),
    '#default_value' => $notification_settings['enabled'],
    '#attributes' => array(
      'class' => array('modules_checklist_notification_enabled'),
    ),
  );

  $form['modules_checklist_notification']['to'] = array(
    '#title' => t('To') . ' <span class="form-required" title="' . t('This field is required.') . '">*</span>',
    '#type' => 'textfield',
    '#description' => t('Enter comma separated email addresses of the recipients.'),
    '#default_value' => $notification_settings['to'],
    '#states' => array(
      'visible' => array(
        ':input.modules_checklist_notification_enabled' => array('checked' => TRUE),
      ),
    ),
  );

  $form['modules_checklist_notification']['subject'] = array(
    '#title' => t('Subject') . ' <span class="form-required" title="' . t('This field is required.') . '">*</span>',
    '#type' => 'textfield',
    '#description' => t('Enter the subject of the email. Supports tokens: !tokens.',
      array('!tokens' => implode(', ', $email_tokens))),
    '#default_value' => $notification_settings['subject'],
    '#states' => array(
      'visible' => array(
        ':input.modules_checklist_notification_enabled' => array('checked' => TRUE),
      ),
    ),
  );

  $form['modules_checklist_notification']['body'] = array(
    '#title' => t('Message') . ' <span class="form-required" title="' . t('This field is required.') . '">*</span>',
    '#type' => 'textarea',
    '#description' => t('Enter the content of the email. Supports tokens: !tokens.',
      array('!tokens' => implode(', ', $email_tokens))),
    '#default_value' => $notification_settings['body'],
    '#states' => array(
      'visible' => array(
        ':input.modules_checklist_notification_enabled' => array('checked' => TRUE),
      ),
    ),
  );

  $form['#attached']['css'][] = drupal_get_path('module', 'modules_checklist') . '/modules_checklist.css';
  $form['#attached']['js'][] = drupal_get_path('module', 'modules_checklist') . '/modules_checklist.js';

  $form['#validate'][] = 'modules_checklist_settings_form_validate';

  return system_settings_form($form);
}

/**
 * Validate handler for the "Generate config" button.
 */
function modules_checklist_settings_form_validate($form, &$form_state) {
  if ($form_state['values']['modules_checklist_notification']['enabled']) {
    if (empty($form_state['values']['modules_checklist_notification']['to'])) {
      form_set_error('modules_checklist_notification][to',
        t('Please fill in required "To" field.'));
    }
    else {
      $mails = explode(',', $form_state['values']['modules_checklist_notification']['to']);

      foreach ($mails as $mail) {
        if (!valid_email_address(trim($mail))) {
          form_set_error('modules_checklist_notification][to',
            t('The syntax of the given e-mail address/addresses is invalid. Enter comma separated valid email addresses.'));
          break;
        }
      }
    }

    if (empty($form_state['values']['modules_checklist_notification']['subject'])) {
      form_set_error('modules_checklist_notification][subject',
        t('Please fill in required "Subject" field.'));
    }

    if (empty($form_state['values']['modules_checklist_notification']['body'])) {
      form_set_error('modules_checklist_notification][body',
        t('Please fill in required "Body" field.'));
    }
  }
}

/**
 * Submit handler for the "Generate $conf variables" button.
 */
function modules_checklist_settings_form_generate_config($form, &$form_state) {
  $messages = array(
    'required' => array(),
    'optional' => array(),
  );
  $config_content = array();
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
    $config_content[] = modules_checklist_get_modules_config_content($data, $type);
  }

  $form_state['storage']['config_content'] = implode("\r\n", $config_content);
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "Reset" button.
 */
function modules_checklist_settings_form_reset($form, &$form_state) {
  drupal_set_message(t('"Configuration helper" table has been flushed and now reflects $conf variables defined in !file.',
    array('!file' => conf_path() . '/settings.php')));
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
    $header = t('Modules Checklist: !flag modules.',
      array('!file' => $config_path, '!flag' => $flag));
    $output = "// " . $header . "\r\n";
    $output .= '$conf[' . "'modules_checklist_" . $flag . "_modules'" . '] = array(' . "\r\n";
    $checked_modules = modules_checklist_get_checked_modules($modules);

    foreach ($checked_modules as $module_machine_name => $module_name) {
      $output .= "  // " . $module_name . ".\r\n";
      $output .= "  '" . $module_machine_name . "',\r\n";
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
