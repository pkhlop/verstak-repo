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

          try{
            db_insert('date_format_type')
              ->fields(array(
                'type' => $date_format['type'],
                'title' => $date_format['title'],
                'locked' => $date_format['locked'],
              ))
              ->execute();

            drush_log(t('Date type [!type !title !locked] has been created.', array(
                '!type' => $date_format['type'],
                '!title' => $date_format['title'],
                '!locked' => $date_format['locked'], )
            ), 'ok');

          } catch(Exception $e) {

            drush_log(t('Date type [!type !title !locked] already exists.', array(
              '!type' => $date_format['type'],
              '!title' => $date_format['title'],
              '!locked' => $date_format['locked'], )
            ), 'ok');

          }

          try {
            db_insert('date_formats')
              ->fields(array(
                'type' => $date_format['type'],
                'format' => $date_format['format'],
                'locked' => $date_format['locked'],
              ))
              ->execute();

            drush_log(t('Date format [!type !format !locked] has been created.', array(
                '!type' => $date_format['type'],
                '!format' => $date_format['format'],
                '!locked' => $date_format['locked'], )
            ), 'ok');

          } catch (Exception $e) {
            drush_log(t('Date format [!type !format !locked] already exists.', array(
                '!type' => $date_format['type'],
                '!format' => $date_format['format'],
                '!locked' => $date_format['locked'], )
            ), 'ok');
          }

          variable_set('date_format_'.$date_format['name'], $date_format['format']);
        }

    }



}
