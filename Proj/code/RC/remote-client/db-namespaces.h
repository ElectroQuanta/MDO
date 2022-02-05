#ifndef DBNAMESPACES_H
#define DBNAMESPACES_H

#include <string>

namespace UserDB
{
  /*USER COLUMNS ID'S*/
  const int ID = 0;
  const int ROLE = 1;
  const int NAME = 2;
  const int EMAIL = 3;
  const int PASS = 4;

  /* Miscellaneous data to build queries*/
  const std::string insert = "INSERT INTO User(role, username, email, pass) values(";
  const std::string _delete = "DELETE FROM User WHERE ";
  const std::string select_all = "SELECT * FROM User";
  const std::string select_where = "SELECT * FROM User WHERE ";
  const std::string select_count = "SELECT count(*) FROM User";
  const std::string select_count_where = "SELECT count(*) FROM User WHERE ";
  const std::string select_role = "SELECT role FROM User WHERE ";
  const std::string update_role = "UPDATE User SET role = ";
}

namespace StationDB {
    /*STATION COLUMNS ID'S*/
    const int ID = 0;
    const int NAME = 1;
    const int LOCATION = 2;
    const int IP = 3;

    /* Miscellaneous data to build queries*/
    const std::string select_all = "SELECT * FROM Station";
    const std::string select_where = "SELECT * from Station WHERE ";
}

namespace AdDB {
    /*Ad COLUMNS ID'S*/
    const int ID = 0;
    const int FRAGRANCE_ID = 1;
    const int USER_ID = 2;
    const int TIMESLOT_ID = 3;
    const int STATION_ID = 4;
    const int FILTER_ID = 5;
    const int ACTIVE = 6;

    /* Miscellaneous data to build queries*/
    const std::string select_all = "SELECT * FROM Ad";
    const std::string select_from_user = "SELECT * FROM Ad WHERE user_id = ";
    const std::string select_from_station = "SELECT * FROM Ad WHERE station_id = ";
    const std::string select_where = "SELECT * from Ad WHERE ";
    const std::string insert = "INSERT INTO Ad(fragrance_id, user_id, timeSlot_id, station_id, filter_id, active) values(";
    const std::string activate = "UPDATE Ad SET active = true WHERE id = ";
    const std::string deactivate = "UPDATE Ad SET active = false WHERE id = ";
    const std::string remove = "DELETE FROM Ad WHERE id = ";
}

namespace TimeTableDB{
    /*TimeTable COLUMNS ID'S*/
    const int ID = 0;
    const int WEEK = 1;
    const int STATION_ID = 2;

    /* Miscellaneous data to build queries*/
    const std::string select_all = "SELECT * FROM TimeTable";
    const std::string select_where = "SELECT * FROM TimeTable WHERE ";
    const std::string select_from_station = "SELECT * FROM TimeTable WHERE station_id = ";
}

namespace TimeSlotDB{
    /*TimeSlot COLUMNS ID'S*/
    const int ID = 0;
    const int TIMETABLE_ID = 1;
    const int DURATION = 2;
    const int COST = 3;

    /* Miscellaneous data to build queries*/
    const std::string select_all = "SELECT * FROM TimeSlot";
    const std::string select_where = "SELECT * FROM TimeSlot WHERE ";
    const std::string select_from_timetable = "SELECT * FROM TimeSlot WHERE timeTable_id = ";
    const std::string delete_where = "DELETE FROM TimeSlot WHERE ";
    const std::string insert = "INSERT INTO TimeSlot(id, timeTable_id, duration, cost) values(";
}

namespace FragranceDB{
    /*Fragrance COLUMNS ID'S*/
    const int ID = 0;
    const int FRAGRANCELIST_ID = 1;
    const int NAME = 2;
    const int INTENSITY = 3;
    const int VOL_MAX = 4;
    const int VOL_LEVEL = 5;
    const int DESCRIPTION = 6;

    /* Miscellaneous data to build queries*/
    const std::string select_all = "SELECT * FROM Fragrance";
    const std::string select_where = "SELECT * FROM Fragrance WHERE ";
    const std::string select_from_fragranceList = "SELECT * FROM Fragrance WHERE fragranceList_id = ";
}

namespace FragranceListDB{
    /*FragranceList COLUMNS ID'S*/
    const int ID = 0;
    const int STATION_ID = 1;

    /* Miscellaneous data to build queries*/
    const std::string select_all = "SELECT * FROM FragranceList";
    const std::string select_where = "SELECT * FROM FragranceList WHERE ";
    const std::string select_from_station = "SELECT * FROM FragranceList WHERE station_id = ";
}

namespace FilterDb {
    /*Filter COLUMNS ID'S*/
    const int ID = 0;
    const int NAME = 1;

    /* Miscellaneous data to build queries*/
    const std::string select_all = "SELECT * FROM Filter";
    const std::string select_where = "SELECT * FROM Filter WHERE ";
}

namespace MediaFileDb {
    /*MediaFile COLUMNS ID'S*/
    const int ID = 0;
    const int AD_ID = 1;
    const int FILENAME = 2;
    const int FILESIZE = 3;
    const int FILETYPE = 4;
    const int MDATA = 5;
    const int DESCRIPTION = 6;

    /* Miscellaneous data to build queries*/
    const std::string select_all = "SELECT * FROM MediaFile";
    const std::string select_where = "SELECT * FROM MediaFile WHERE ";
    const std::string insert = "INSERT INTO MediaFile(ad_id, filename, filesize, filetype) values(";
}
#endif // DBNAMESPACES_H
