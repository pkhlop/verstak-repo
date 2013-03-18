<?php

require_once __DIR__.'/conf/import_config.inc';
require_once __DIR__.'/lib/init.inc';

global $user;
$user = user_load(1);

//echo "Start Date Format Import ==========================\n";
//$storage = new DateFormatStorage(ImportConfig::getConfig()->importer_path.'/data/date_format/*.inc');
//$importer = new DateFormatImporter($storage);
//$importer->Import();

//echo "Start Content Type Import ==========================\n";
//$storage = new ContentTypeStorage(ImportConfig::getConfig()->importer_path.'/data/content_type/*.inc');
//$importer = new ContentTypeImporter($storage);
//$importer->Import();
//
//echo "Start Input Format Import ==========================\n";
//$storage = new InputFormatStorage(ImportConfig::getConfig()->importer_path.'/data/input_formats/*.inc');
//$importer = new InputFormatImporter($storage);
//$importer->Import();
//
////echo "Start Taxonomy Import ==========================\n";
////$storage = new TaxonomyStorage(ImportConfig::getConfig()->importer_path.'/data/taxonomy/*.inc');
////$importer = new TaxonomyImporter($storage);
////$importer->Import();
//
//echo "Start ImageCache Presets Outline ==========================\n";
//$storage = new ImageCacheStorage(ImportConfig::getConfig()->importer_path.'/data/presets/*.inc');
//$importer = new ImageCacheImporter($storage);
//$importer->Import();
//
//echo "Start Views Import ==========================\n";
//$storage = new ViewsStorage(ImportConfig::getConfig()->importer_path.'/data/views/*.inc');
//$importer = new ViewsImporter($storage);
//$importer->Import();
//
////echo "Start Node Import ==========================\n";
////$storage = new NodeStorage(ImportConfig::getConfig()->importer_path.'/data/nodes/*.inc');
////$importer = new NodeImporter($storage);
////$importer->Import();
//
//echo "Start Menu Import ==========================\n";
//$storage = new MenuStorage(ImportConfig::getConfig()->importer_path.'/data/menus/*.inc');
//$importer = new MenuImporter($storage);
//$importer->Import();
//
//echo "Start Block Outline ==========================\n";
//$storage = new BlockStorage(ImportConfig::getConfig()->importer_path.'/data/blocks/*.inc');
//$importer = new BlockImporter($storage);
//$importer->Import();
//
//echo "Start Profile Fields Creation ==========================\n";
//$storage = new ProfileFieldsStorage(ImportConfig::getConfig()->importer_path.'/data/profile/*.inc');
//$importer = new ProfileFieldsImporter($storage);
//$importer->Import();

variable_set('custom_pub_types',
	array (
		'show_in_menu' =>
		array (
			'type' => 'show_in_menu',
			'name' => 'Show in menu',
			'node_types' =>
			array (
				'article' => 'Article',
				'set' => 'Set',
			),
		),
		'show_in_fp_ss' =>
		array (
			'type' => 'show_in_fp_ss',
			'name' => 'Show in front page slide show',
			'node_types' =>
			array (
				'article' => 'Article',
				'set' => 'Set',
			),
		),
		'show_in_featured' =>
		array (
			'type' => 'show_in_featured',
			'name' => 'Show in Featured',
			'node_types' =>
			array (
				'article' => 'Article',
				'set' => 'Set',
			),
		),
		'show_in_cat_ss' =>
		array (
			'type' => 'show_in_cat_ss',
			'name' => 'Show in Category slideshow',
			'node_types' =>
			array (
				'article' => 'Article',
				'set' => 'Set',
			),
		),
		'test_content' =>
		array (
			'type' => 'test_content',
			'name' => 'Test Content',
			'node_types' =>
			array (
				'article' => 'Article',
				'set' => 'Set',
			),
		),
		'dependent' =>
		array (
			'type' => 'dependent',
			'name' => 'Dependent',
			'node_types' =>
			array (
				'article' => 'Article',
			),
		),
		'wire_news' =>
		array (
			'type' => 'wire_news',
			'name' => 'WireNews',
			'node_types' =>
			array (
				'article' => 'Article',
				'set' => 'List',
			),
		),
	)
);
try{


db_query("ALTER TABLE {node}
	ADD COLUMN 	`show_in_menu` INT(11) NOT NULL DEFAULT '0' COMMENT 'Custom publishing option Show in menu',
	ADD COLUMN 	`show_in_fp_ss` INT(11) NOT NULL DEFAULT '0' COMMENT 'Custom puищфblishing option Show in front page slide show',
	ADD COLUMN 	`show_in_featured` INT(11) NOT NULL DEFAULT '0' COMMENT 'Custom publishing option Show in Featured',
	ADD COLUMN 	`show_in_cat_ss` INT(11) NOT NULL DEFAULT '0' COMMENT 'Custom publishing option Show in Category slideshow',
	ADD COLUMN 	`test_content` INT(11) NOT NULL DEFAULT '0' COMMENT 'Custom publishing option Test Content',
	ADD COLUMN 	`dependent` INT(11) NOT NULL DEFAULT '0' COMMENT 'Custom publishing option Dependent',
	ADD COLUMN 	`wire_news` INT(11) NOT NULL DEFAULT '0' COMMENT 'Custom publishing option WireNews';")->execute();
}catch (Exception $e) {
	echo "ALTER TABLE {node} Failed!";
}

variable_set("cache", 1);
variable_set("page_compression", 1);
variable_set("block_cache", 1);

variable_set("preprocess_css", 0);
variable_set("preprocess_js", 0);
