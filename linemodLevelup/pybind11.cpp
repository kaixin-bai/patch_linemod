#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "np2mat/ndarray_converter.h"
#include "linemodLevelup.h"
namespace py = pybind11;

PYBIND11_MODULE(linemodLevelup_pybind, m) {
    NDArrayConverter::init_numpy();

    py::class_<linemodLevelup::Match>(m,"Match")
            .def(py::init<>())
            .def_readwrite("x",&linemodLevelup::Match::x)
            .def_readwrite("y",&linemodLevelup::Match::y)
            .def_readwrite("similarity",&linemodLevelup::Match::similarity)
            .def_readwrite("class_id",&linemodLevelup::Match::class_id)
            .def_readwrite("template_id",&linemodLevelup::Match::template_id);

    py::class_<linemodLevelup::Template>(m,"Template")
            .def(py::init<>())
            .def_readwrite("width",&linemodLevelup::Template::width)
            .def_readwrite("height",&linemodLevelup::Template::height)
            .def_readwrite("pyramid_level",&linemodLevelup::Template::pyramid_level);


    py::class_<linemodLevelup::Detector>(m, "Detector")
        .def(py::init<>())
        .def(py::init<std::vector<int>, int>())
        .def(py::init<int, std::vector<int>, int>())
        .def("addTemplate", &linemodLevelup::Detector::addTemplate)
        .def("writeClasses", &linemodLevelup::Detector::writeClasses)
        .def("clear_classes", &linemodLevelup::Detector::clear_classes)
        .def("readClasses", &linemodLevelup::Detector::readClasses)
        .def("match", &linemodLevelup::Detector::match, py::arg("sources"),
             py::arg("threshold"), py::arg("active_ratio"), py::arg("class_ids"),
             py::arg("dep_anchors"), py::arg("dep_range"), py::arg("masks")=cv::Mat())
        .def("getTemplates", &linemodLevelup::Detector::getTemplates)
            .def("numTemplates", &linemodLevelup::Detector::numTemplates);

    m.def("matches2poses", &poseRefine_adaptor::matches2poses,
          py::arg("matches"), py::arg("detector"), py::arg("saved_poses"),
          py::arg("K")=cv::Mat(), py::arg("top100")=100);
}
