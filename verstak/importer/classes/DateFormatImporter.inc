<?php
class DateFormatImporter{
    private $storage;



    public function __construct(DateFormatStorage $storage) {
        $this->storage = $storage;
    }
    
    public function Import(){
        
        $this->storage->Load();

        $date_formats = $this->storage->Get();
        
        foreach ($date_formats as $date_format){

         db_query("INSERT INTO {date_format_types} (type, title, locked) VALUES ('%s', '%s', %d)",
                 $date_format['name'], $date_format['title'],$date_format['locked']);
            
         db_query("INSERT INTO {date_formats} (format, type, locked) VALUES ('%s', '%s', %d)",
                 $date_format['format'], $date_format['type'],$date_format['locked']);

         variable_set('date_format_'.$date_format['name'], $date_format['format']);
        }
        
    }

    

}
