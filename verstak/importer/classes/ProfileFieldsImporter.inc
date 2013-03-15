<?php

class ProfileFieldsImporter{
    private $storage;
    
    public function __construct(ProfileFieldsStorage $storage) {
        $this->storage = $storage;
    }
    
    public function Import(){
        $this->storage->Load();
        $profile_fields = $this->storage->Get();
        
        
        foreach ($profile_fields as $profile_field){
          db_query("
            INSERT INTO {profile_fields} 
            (title, name, explanation, category, type, weight, required, register, visibility, autocomplete, options, page)
            VALUES ('%s', '%s', '%s', '%s', '%s', %d, %d, %d, %d, %d, '%s', '%s')",
            $profile_field['title'],
            $profile_field['name'],
            $profile_field['explanation'],
            $profile_field['category'],
            $profile_field['type'],
            $profile_field['weight'],
            $profile_field['required'],
            $profile_field['register'],
            $profile_field['visibility'],
            $profile_field['autocomplete'],
            $profile_field['options'],
            $profile_field['page']
          );
          drupal_set_message(t('The field %field has been created under category %category.', array('%field' => $profile_field['title'], '%category' => $profile_field['category'])));
          watchdog('profile', 'Profile field %field added under category %category.', array('%field' => $profile_field['title'], '%category' => $profile_field['category']), WATCHDOG_NOTICE, l(t('view'), 'admin/user/profile'));
        }
               
    }
    
}