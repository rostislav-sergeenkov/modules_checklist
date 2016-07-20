<?php

/**
 * @file
 * File modules_checklist_log.views_default.inc.
 */

/**
 * Implements hook_views_default_views().
 */
function modules_checklist_log_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'modules_checklist_log';
  $view->description = t('Administration UI for browsing modules_checklist events.');
  $view->tag = 'default';
  $view->base_table = 'modules_checklist_log';
  $view->human_name = 'Modules Checklist log';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = t('Modules Checklist Log');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access modules_checklist log';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'module_name' => 'module_name',
    'status' => 'status',
    'type' => 'type',
    'name' => 'name',
    'ip' => 'ip',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['style_options']['default'] = 'id';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'module_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ip' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = t('No results found.');
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Relationship: Modules Checklist log entry: User information. */
  $handler->display->display_options['relationships']['author_info']['id'] = 'author_info';
  $handler->display->display_options['relationships']['author_info']['table'] = 'modules_checklist_log';
  $handler->display->display_options['relationships']['author_info']['field'] = 'author_info';
  $handler->display->display_options['relationships']['author_info']['required'] = TRUE;
  /* Field: Modules Checklist log entry: Log entry ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  /* Field: Modules Checklist log entry: Module Name */
  $handler->display->display_options['fields']['module_name']['id'] = 'module_name';
  $handler->display->display_options['fields']['module_name']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['module_name']['field'] = 'module_name';
  $handler->display->display_options['fields']['module_name']['element_label_colon'] = FALSE;
  /* Field: Modules Checklist log entry: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = t('Config Status');
  $handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
  /* Field: Modules Checklist log entry: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = t('Event Type');
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'author_info';
  $handler->display->display_options['fields']['name']['label'] = t('User');
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Modules Checklist log entry: IP address */
  $handler->display->display_options['fields']['ip']['id'] = 'ip';
  $handler->display->display_options['fields']['ip']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['ip']['field'] = 'ip';
  $handler->display->display_options['fields']['ip']['element_label_colon'] = FALSE;
  /* Field: Modules Checklist log entry: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Date';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  /* Filter criterion: Modules Checklist log entry: Module Name */
  $handler->display->display_options['filters']['module_name']['id'] = 'module_name';
  $handler->display->display_options['filters']['module_name']['table'] = 'modules_checklist_log';
  $handler->display->display_options['filters']['module_name']['field'] = 'module_name';
  $handler->display->display_options['filters']['module_name']['group'] = 1;
  $handler->display->display_options['filters']['module_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['module_name']['expose']['operator_id'] = 'module_name_op';
  $handler->display->display_options['filters']['module_name']['expose']['label'] = t('Module Name');
  $handler->display->display_options['filters']['module_name']['expose']['operator'] = 'module_name_op';
  $handler->display->display_options['filters']['module_name']['expose']['identifier'] = 'module_name';
  $handler->display->display_options['filters']['module_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Modules Checklist log entry: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'modules_checklist_log';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = t('Config Status');
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Modules Checklist log entry: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'modules_checklist_log';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = t('Event Type');
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'author_info';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = t('User');
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Modules Checklist log entry: IP address */
  $handler->display->display_options['filters']['ip']['id'] = 'ip';
  $handler->display->display_options['filters']['ip']['table'] = 'modules_checklist_log';
  $handler->display->display_options['filters']['ip']['field'] = 'ip';
  $handler->display->display_options['filters']['ip']['group'] = 1;
  $handler->display->display_options['filters']['ip']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ip']['expose']['operator_id'] = 'ip_op';
  $handler->display->display_options['filters']['ip']['expose']['label'] = t('IP address');
  $handler->display->display_options['filters']['ip']['expose']['operator'] = 'ip_op';
  $handler->display->display_options['filters']['ip']['expose']['identifier'] = 'ip';
  $handler->display->display_options['filters']['ip']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'admin/reports/modules_checklist_log';

  $export['modules_checklist_log'] = $view;

  return $export;
}
