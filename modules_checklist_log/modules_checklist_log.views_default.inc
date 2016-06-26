<?php

/**
 * @file
 * modules_checklist_log.views_default.inc.
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
  $view->human_name = t('Modules Checklist log');
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Modules Checklist log';
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
    'module_name' => 'module_name',
    'type' => 'type',
    'name' => 'name',
    'timestamp' => 'timestamp',
  );
  $handler->display->display_options['style_options']['default'] = 'timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'module_name' => array(
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
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
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
  /* Relationship: Modules Checklist Log Entry: User information. */
  $handler->display->display_options['relationships']['author_info']['id'] = 'author_info';
  $handler->display->display_options['relationships']['author_info']['table'] = 'modules_checklist_log';
  $handler->display->display_options['relationships']['author_info']['field'] = 'author_info';
  $handler->display->display_options['relationships']['author_info']['required'] = TRUE;
  /* Field: Modules Checklist Log Entry: Module Name */
  $handler->display->display_options['fields']['module_name']['id'] = 'module_name';
  $handler->display->display_options['fields']['module_name']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['module_name']['field'] = 'module_name';
  $handler->display->display_options['fields']['module_name']['element_label_colon'] = FALSE;
  /* Field: Modules Checklist Log Entry: Status */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'author_info';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Modules Checklist Log Entry: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'modules_checklist_log';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  /* Filter criterion: Modules Checklist Log Entry: Module Name */
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
  /* Filter criterion: Modules Checklist Log Entry: Status */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'modules_checklist_log';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = t('Status');
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['path'] = 'admin/reports/modules_checklist_log';

  $export['modules_checklist_log'] = $view;

  return $export;
}
