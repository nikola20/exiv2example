
// exiv2exaplme.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "exiv2\exiv2.hpp"
#include <fstream>
#include "Jzon.h"
#include <string>
using std::ofstream;
using std::string;

//image examples for metadata extraction:
//https://github.com/ianare/exif-samples/tree/master/jpg

int main()
{
	ofstream f1, f2, f3;
	f1.open("file1.txt");

	Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open("C:\\Users\\Nidza\\source\\repos\\Exiv2 example\\x64\\Release\\BlueSquare.jpg");

	image->readMetadata();
	Exiv2::ExifData &exifData = image->exifData();

	Exiv2::ExifData::const_iterator end = exifData.end();
	for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
		const char* tn = i->typeName();
		f1 << std::setw(44) << std::setfill(' ') << std::left
			<< i->key() << " "
			<< "0x" << std::setw(4) << std::setfill('0') << std::right
			<< std::hex << i->tag() << " "
			<< std::setw(9) << std::setfill(' ') << std::left
			<< (tn ? tn : "Unknown") << " "
			<< std::dec << std::setw(3)
			<< std::setfill(' ') << std::right
			<< i->count() << "  "
			<< std::dec << i->value()
			<< "\n";
	}
	f1 << std::endl;
	Exiv2::IptcData &iptcData = image->iptcData();
	for (Exiv2::IptcData::iterator md = iptcData.begin(); md != iptcData.end(); ++md) {
		f1 << std::setw(44) << std::setfill(' ') << std::left
			<< md->key() << " "
			<< "0x" << std::setw(4) << std::setfill('0') << std::right
			<< std::hex << md->tag() << " "
			<< std::setw(9) << std::setfill(' ') << std::left
			<< md->typeName() << " "
			<< std::dec << std::setw(3)
			<< std::setfill(' ') << std::right
			<< md->count() << "  "
			<< std::dec << md->value()
			<< std::endl;
	}
	f1 << std::endl;
	Exiv2::XmpData & xmpData = image->xmpData();
	for (Exiv2::XmpData::const_iterator md = xmpData.begin();
		md != xmpData.end(); ++md) {
		f1 << std::setfill(' ') << std::left
			<< std::setw(44)
			<< md->key() << " "
			<< std::setw(9) << std::setfill(' ') << std::left
			<< md->typeName() << " "
			<< std::dec << std::setw(3)
			<< std::setfill(' ') << std::right
			<< md->count() << "  "
			<< std::dec << md->value()
			<< std::endl;
	}

	f1.close();

	f2.open("file2.txt");

	Exiv2::ExifData & exifData1 = image->exifData();

	Jzon::Node root = Jzon::object();
	Jzon::Writer wr;
	Jzon::Format f;
	f.indentSize = 1;
	f.newline = true;
	f.spacing = true;
	f.useTabs = false;
	wr.setFormat(f);
	for (auto & a : exifData1) {
		root.add(a.tagName(), a.value().toString());
	}
	string a;
	wr.writeString(root, a);
	f2 << a;

	Exiv2::IptcData & iptcData1 = image->iptcData();

	root.clear();
	for (auto & a : iptcData1) {
		root.add(a.tagName(), a.value().toString());
	}
	string a1;
	wr.writeString(root, a1);
	f2 << a1;

	Exiv2::XmpData & xmpData1 = image->xmpData();

	root.clear();

	for (auto & a : xmpData1) {
		root.add(a.tagName(), a.value().toString());
	}
	string a2;
	wr.writeString(root, a2);
	f2 << a2;
	
	f2.close();


    return 0;
}

