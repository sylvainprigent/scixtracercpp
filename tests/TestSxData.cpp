#include "SxTestConfig.h"
#include <scixtracer>

#include "CreateMetadata.h"
#include "SxCompare.h"
#include "SxSerializeJson.h"

#include <QFile>
#include <QDebug>

void tearDown(){
    QFile qt_tst_raw_file(tst_rawdata_file);
    if (qt_tst_raw_file.exists()){
        qt_tst_raw_file.remove();
    }

    QFile qt_tst_processeddata_file(tst_processeddata_file);
    if (qt_tst_processeddata_file.exists()){
        qt_tst_processeddata_file.remove();
    }
}

bool test_read_rawdata()
{
    try {
        SxRequestLocal request;
        SxRawData* rawData = request.read_rawdata(ref_rawdata_file1);
        SxRawData* raw_data_ref_metadata = create_raw_data();

        SxSerializeJson serializer;
        QString ser1 = serializer.serialize(raw_data_ref_metadata);
        QString ser2 = serializer.serialize(rawData);

        //qDebug() << ser1;
        //qDebug() << ser2;
        if (ser1 == ser2)
        {
            return 0;
        }
        return 1;
    }
    catch (SxException& e)
    {
        qDebug() << "SxException: " << e.what();
        return 1;
    }
}

bool test_write_rawdata()
{
    SxRawData* raw_data = create_raw_data();
    raw_data->set_md_uri(tst_rawdata_file);

    SxRequestLocal request;
    request.write_rawdata(raw_data, ref_rawdata_file1);

    return SxCompare::compare_txt_files(tst_rawdata_file, ref_rawdata_file1);
}

int main(int argc, char* argv[])
{

    if (test_read_rawdata())
    {
        return 1;
    }

    if (test_write_rawdata())
    {
        return 1;
    }

    /*


    def test_read_processeddata(self):
        processed_data_read = ProcessedData(self.ref_processeddata_file)  
        processed_data_ref_metadata = create_processed_data()
        self.assertEqual(processed_data_read.metadata.serialize(),
                         processed_data_ref_metadata.serialize())

    def test_write_processeddata(self):
        processed_data = ProcessedData(self.tst_processeddata_file)
        processed_data.metadata = create_processed_data()
        processed_data.write()
        self.assertTrue(filecmp.cmp(self.tst_processeddata_file,
                                    self.ref_processeddata_file,
                                    shallow=False))

    def test_processeddata_parent(self):
        processed_data = ProcessedData(self.ref_processeddata2_file)
        parent_data = processed_data.get_parent()
        self.assertEqual(parent_data.metadata.name, 'population1_001_o')

    def test_processeddata_origin(self):
        processed_data = ProcessedData(self.ref_processeddata2_file)
        parent_data = processed_data.get_origin()
        self.assertEqual(parent_data.metadata.name, 'population1_001.tif')
      */

      tearDown();
}
