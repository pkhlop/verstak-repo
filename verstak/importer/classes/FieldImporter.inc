<?php
class FieldImporter{
    private $storage;
    public function __construct(FieldStorage $storage) {
        $this->storage = $storage;
    }
    public function Import(){
        $this->storage->Load();
        $fields = $this->storage->Get();
        
        module_load_include('inc', 'content', 'includes/content.crud');
        
        foreach ($fields as $field){
            content_field_instance_create($field, false);
            content_clear_type_cache(TRUE);
	    menu_rebuild();
        }
        
    }
    
}