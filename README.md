# VocXmlAnnotationConverter
将自定义的标注格式转换为voc的xml格式，可用于faster rcnn训练

###Annotation Format
E:/data/image_0001.jpg	2	ChinaFlag	100	100	200	200	KoreaFlag	112	112	212	212
E:/data/image_0002.jpg	2	ChinaFlag	111	222	333	444	KoreaFlag	555	666	777	888
**Note:** 分隔符是Tab键
###Generated VOC xml format
<annotation>
	<folder>VOC2012</folder>
	<filename>image_0001.jpg</filename>
	<source>
		<database>The VOC2007 Database</database>
		<annotation>PASCAL VOC2007</annotation>
		<image>flickr</image>
		<flickrid></flickrid>
	</source>
	<owner>
		<flickrid>Fried Camels</flickrid>
		<name>Jinky the Fruit Bat</name>
	</owner>
	<size>
		<width>500</width>
		<height>600</height>
		<depth>1</depth>
	</size>
	<segmented>0</segmented>
	<object>
		<name>ChinaFlag</name>
		<pose></pose>
		<truncated>1</truncated>
		<difficult>0</difficult>
		<bndbox>
			<xmin>100</xmin>
			<ymin>100</ymin>
			<xmax>200</xmax>
			<ymax>200</ymax>
		</bndbox>
	</object>
	<object>
		<name>KoreaFlag</name>
		<pose></pose>
		<truncated>1</truncated>
		<difficult>0</difficult>
		<bndbox>
			<xmin>112</xmin>
			<ymin>112</ymin>
			<xmax>212</xmax>
			<ymax>212</ymax>
		</bndbox>
	</object>
</annotation>
