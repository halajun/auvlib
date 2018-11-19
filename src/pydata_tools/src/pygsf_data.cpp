#include <data_tools/gsf_data.h>

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include <pybind11/stl.h>

namespace py = pybind11;

/*
 * Screw this for now. Idea would be to instantiate a class
 * and automatically get the member pointer from the instance
 * by subtracting the class offset from the pointer. if pybind
 * accepts merely the type pointer (as opposed to member pointer
 * this should be fine. But it's a bit to hacky and risky for now
 */

/*
template <typename T>
class PybindCerealArchive {

private:

    py::class_<T>& c;

public:

    PybindCerealArchive(py::class_<T>& c) : c(c) {}

    template <typename A>
    void bind_values(A&& key_value)
    {
        c.def_readwrite(key_value.name, key_value.value);
    }

    template<typename ... Args>
    void operator()(Args&& ... args)
    {
        bind_values(args)...;
    }

};
*/

PYBIND11_MODULE(gsf_data, m) {
    m.doc() = "Basic utilities for working with the .gsf file format"; // optional module docstring

    py::class_<gsf_mbes_ping>(m, "gsf_mbes_ping", "Class for the gsf multibeam type")
        .def(py::init<>())
        .def_readwrite("time_string_", &gsf_mbes_ping::time_string_, "Member")
        .def_readwrite("time_stamp_", &gsf_mbes_ping::time_stamp_, "Member")
        .def_readwrite("travel_times", &gsf_mbes_ping::travel_times, "Member")
        .def_readwrite("beam_angles", &gsf_mbes_ping::beam_angles, "Member")
        .def_readwrite("distances", &gsf_mbes_ping::distances, "Member")
        .def_readwrite("amplitudes", &gsf_mbes_ping::amplitudes, "Member")
        .def_readwrite("first_in_file_", &gsf_mbes_ping::first_in_file_, "Member")
        .def_readwrite("heading_", &gsf_mbes_ping::heading_, "Member")
        .def_readwrite("pitch_", &gsf_mbes_ping::pitch_, "Member")
        .def_readwrite("roll_", &gsf_mbes_ping::roll_, "Member")
        .def_readwrite("lat_", &gsf_mbes_ping::lat_, "Member")
        .def_readwrite("long_", &gsf_mbes_ping::long_, "Member")
        .def_readwrite("depth_", &gsf_mbes_ping::depth_, "Member")
        .def_readwrite("beams", &gsf_mbes_ping::beams, "Member")
        .def_static("parse_file", &parse_file_from_str<gsf_mbes_ping>, "Parse gsf_mbes_ping from .gsf file")
        .def_static("parse_folder", &parse_folder_from_str<gsf_mbes_ping>, "Parse gsf_mbes_ping from folder of .gsf files")
        .def_static("read_data", &read_data_from_str<gsf_mbes_ping::PingsT>, "Read gsf_mbes_ping::PingsT from .cereal file");
    //PybindCerealArchive<gsf_mbes_ping> archive(c);
    //gsf_mbes_ping example; example.serialize(archive);

    py::class_<gsf_sound_speed>(m, "gsf_sound_speed", "Class for the gsf sound speed type")
        .def(py::init<>())
        .def_readwrite("time_string_", &gsf_sound_speed::time_string_, "Member")
        .def_readwrite("time_stamp_", &gsf_sound_speed::time_stamp_, "Member")
        .def_readwrite("near_speed", &gsf_sound_speed::near_speed, "Member")
        .def_readwrite("below_speed", &gsf_sound_speed::below_speed, "Member")
        .def_static("parse_file", &parse_file_from_str<gsf_sound_speed>, "Parse gsf_sound_speed from .gsf file")
        .def_static("parse_folder", &parse_folder_from_str<gsf_sound_speed>, "Parse gsf_sound_speed from folder of .gsf files")
        .def_static("read_data", &read_data_from_str<gsf_sound_speed::SpeedsT>, "Read gsf_sound_speed::SpeedsT from .cereal file");

    py::class_<gsf_nav_entry>(m, "gsf_nav_entry", "Class for the gsf nav entry type")
        .def(py::init<>())
        .def_readwrite("id_", &gsf_nav_entry::id_, "Member")
        .def_readwrite("time_string_", &gsf_nav_entry::time_string_, "Member")
        .def_readwrite("time_stamp_", &gsf_nav_entry::time_stamp_, "Member")
        .def_readwrite("roll_", &gsf_nav_entry::roll_, "Member")
        .def_readwrite("pitch_", &gsf_nav_entry::pitch_, "Member")
        .def_readwrite("yaw_", &gsf_nav_entry::yaw_, "Member")
        .def_readwrite("lat_", &gsf_nav_entry::lat_, "Member")
        .def_readwrite("long_", &gsf_nav_entry::long_, "Member")
        .def_readwrite("altitude", &gsf_nav_entry::altitude, "Member")
        .def_readwrite("pos_", &gsf_nav_entry::pos_, "Member")
        .def_static("parse_file", &parse_file_from_str<gsf_nav_entry>, "Parse gsf_nav_entry from .gsf file")
        .def_static("parse_folder", &parse_folder_from_str<gsf_nav_entry>, "Parse gsf_nav_entry from folder of .gsf files")
        .def_static("read_data", &read_data_from_str<gsf_nav_entry::EntriesT>, "Read gsf_nav_entry::EntriesT from .cereal file");

    m.def("write_data", &write_data_from_str<gsf_mbes_ping::PingsT>, "Write gsf_mbes_ping::PingsT to .cereal file");
    m.def("write_data", &write_data_from_str<gsf_nav_entry::EntriesT>, "Write gsf_nav_entry::EntriesT to .cereal file");
    m.def("write_data", &write_data_from_str<gsf_sound_speed::SpeedsT>, "Write gsf_sound_speed::SpeedsT to a .cereal file");
    m.def("convert_pings", &convert_pings, "Convert gsf_mbes_ping::EntriesT to mbes_ping::EntriesT");
}
