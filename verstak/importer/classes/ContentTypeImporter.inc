<?php
class ContentTypeImporter{
  private $storage;

  public function __construct(ContentTypeStorage $storage) {
    $this->storage = $storage;
  }

  public function Import(){
    $this->storage->Load();
    $types = $this->storage->Get();

    $values = array();
    $values['values']['type_name'] ='<create>';
    foreach ($types as $type){
        $values['values']['macro'] = $type['macro'];
        echo "Import content: ".$type['name']."\n";
        drupal_form_submit("bundle_copy_import", $values);
        drupal_flush_all_caches();
        menu_rebuild();
    }
  }
}