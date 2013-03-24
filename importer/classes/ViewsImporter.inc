<?php
class ViewsImporter{
    private $storage;
    
    public function __construct(ViewsStorage $storage) {
        $this->storage = $storage;
    }
    
    public function Import(){
        $this->storage->Load();
        $views = $this->storage->Get();
        foreach ($views as $view){
          drush_log(t('Import !view.', array('!view' => $view['name'],)), 'ok');
          $this->view_import($view['name'], $view['macro']);
        }
    }
    
    private function view_import($view_name, $view_macro) {
      include_once(drupal_get_path('module', 'views') .'/views.module');
      include_once(drupal_get_path('module', 'views') .'/includes/view.inc');
      include_once(drupal_get_path('module', 'views') .'/includes/cache.inc');
      //include_once(drupal_get_path('module', 'views') .'/includes/convert.inc'); 
      include_once(drupal_get_path('module', 'views') .'/includes/admin.inc');
      
      $form_state['values']['name'] = $view_name;
      $form_state['values']['view'] = $view_macro;
      $form_state['values']['op'] = t('Import');
      
      drupal_form_submit('views_ui_import_page', $form_state);

      eval($view_macro);

      views_ui_cache_load($view_name);

      $view->save();
      return $view->vid;
    }
}