// exiv2exaplme.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "exiv2\exiv2.hpp"
#include <fstream>
#include "Jzon.h"
#include <string>
using std::ofstream;
using std::string;

/*

{
"FS": {
"path": "\/Users\/rmills\/Downloads\/BabyGnuTux-BigWLPG.jpg",
"realpath": "\/Users\/rmills\/Downloads\/BabyGnuTux-BigWLPG.jpg",
"st_dev": 16777220,
"st_ino": 51155556,
"st_mode": 33188,
"st_nlink": 1,
"st_uid": 501,
"st_gid": 20,
"st_rdev": 0,
"st_size": 121943,
"st_atime": 1428657394,
"st_mtime": 1427548635,
"st_ctime": 1427548635,
"st_blksize": 4096,
"st_blocks": 240
},
"Exif": {
"Image": {
"Orientation": 1,
"XResolution": [
720090,
10000
],
"YResolution": [
720090,
10000
],
"ResolutionUnit": 2,
"Software": "Adobe Photoshop CS5 Windows",
"DateTime": "2012:01:04 20:34:45",
"ExifTag": 164
},
"Photo": {
"ColorSpace": 1,
"PixelXDimension": 1600,
"PixelYDimension": 800
},
"Thumbnail": {
"Compression": 6,
"XResolution": [
72,
1
],
"YResolution": [
72,
1
],
"ResolutionUnit": 2,
"JPEGInterchangeFormat": 302,
"JPEGInterchangeFormatLength": 3586
}
},
"Xmp": {
"xmp": {
"CreatorTool": "Adobe Photoshop CS5 Windows",
"CreateDate": "2012-01-04T20:32:52+01:00",
"ModifyDate": "2012-01-04T20:34:45+01:00",
"MetadataDate": "2012-01-04T20:34:45+01:00"
},
"dc": {
"format": "image\/jpeg"
},
"photoshop": {
"ColorMode": "3",
"ICCProfile": "sRGB IEC61966-2.1"
},
"xmpMM": {
"InstanceID": "xmp.iid:4E9C1E280B37E111A568FF94F417581A",
"DocumentID": "xmp.did:4D9C1E280B37E111A568FF94F417581A",
"OriginalDocumentID": "xmp.did:4D9C1E280B37E111A568FF94F417581A",
"History": [
{
"stEvt": {
"action": "created",
"instanceID": "xmp.iid:4D9C1E280B37E111A568FF94F417581A",
"when": "2012-01-04T20:32:52+01:00",
"softwareAgent": "Adobe Photoshop CS5 Windows"
}
},
{
"stEvt": {
"action": "converted",
"parameters": "from image\/png to image\/jpeg"
}
},
{
"stEvt": {
"action": "saved",
"instanceID": "xmp.iid:4E9C1E280B37E111A568FF94F417581A",
"when": "2012-01-04T20:34:45+01:00",
"softwareAgent": "Adobe Photoshop CS5 Windows",
"changed": "\/"
}
}
]
},
"MP": {
"RegionInfo": {
"MPRI": {
"Regions": [
{
"MPReg": {
"Rectangle": "0.661608, 0.244310, 0.130501, 0.261002",
"PersonDisplayName": "Baby Tux"
}
},
{
"MPReg": {
"Rectangle": "0.205615, 0.226100, 0.130501, 0.261002",
"PersonDisplayName": "Baby Gnu"
}
}
]
}
}
}
}
}

*/

//image examples for metadata extraction:
//https://github.com/ianare/exif-samples/tree/master/jpg

int main()
{
	Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open("C:\\Users\\Nidza\\source\\repos\\Exiv2 example\\x64\\Release\\BlueSquare.jpg");
	
	image->readMetadata();
	
	Exiv2::ExifData & exifData = image->exifData();
	Exiv2::IptcData & iptcData = image->iptcData();
	Exiv2::XmpData & xmpData = image->xmpData();

	Jzon::Node root = Jzon::object();
	Jzon::Node exifNode = Jzon::object();
	Jzon::Node iptcNode = Jzon::object();
	Jzon::Node xmpNode = Jzon::object();

	


	Jzon::Writer wr;
	Jzon::Format f;
	f.indentSize = 1;
	f.newline = true;
	f.spacing = true;
	f.useTabs = false;
	wr.setFormat(f);

	for (auto & a : exifData) {
		exifNode.add(a.tagName(), a.value().toString());
	}

	for (auto & a : iptcData) {
		iptcNode.add(a.tagName(), a.value().toString());
	}

	for (auto & a : xmpData) {
		xmpNode.add(a.tagName(), a.value().toString());
	}

	root.add("exif", exifNode);
	root.add("iptc", iptcNode);
	root.add("xmp", xmpNode);

	wr.writeFile(root, "file1.txt");

    return 0;
}

