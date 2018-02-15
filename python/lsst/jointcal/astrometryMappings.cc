/*
 * LSST Data Management System
 *
 * This product includes software developed by the
 * LSST Project (http://www.lsst.org/).
 * See the COPYRIGHT file
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the LSST License Statement and
 * the GNU General Public License along with this program.  If not,
 * see <https://www.lsstcorp.org/LegalNotices/>.
 */

#include "pybind11/pybind11.h"

#include "lsst/jointcal/Gtransfo.h"
#include "lsst/jointcal/AstrometryMapping.h"
#include "lsst/jointcal/TwoTransfoMapping.h"

namespace py = pybind11;
using namespace pybind11::literals;

namespace lsst {
namespace jointcal {
namespace {

void declareAstrometryMapping(py::module &mod) {
    py::class_<AstrometryMapping, std::shared_ptr<AstrometryMapping>> cls(mod, "AstrometryMapping");

    cls.def("getNpar", &AstrometryMapping::getNpar);
    cls.def("transformPosAndErrors", [](AstrometryMapping const &self, jointcal::FatPoint &inPos) {
        jointcal::FatPoint outPos;
        self.transformPosAndErrors(inPos, outPos);
        return outPos;
    });
}

void declareTwoTransfoMapping(py::module &mod) {
    py::class_<TwoTransfoMapping, std::shared_ptr<TwoTransfoMapping>, AstrometryMapping> cls(
            mod, "TwoTransfoMapping");

    cls.def("getTransfo1", &TwoTransfoMapping::getTransfo1, py::return_value_policy::reference_internal);
    cls.def_property_readonly("transfo1", &TwoTransfoMapping::getTransfo1,
                              py::return_value_policy::reference_internal);

    cls.def("getTransfo2", &TwoTransfoMapping::getTransfo2, py::return_value_policy::reference_internal);
    cls.def_property_readonly("transfo2", &TwoTransfoMapping::getTransfo2,
                              py::return_value_policy::reference_internal);
}

void declareSimpleGtransfoMapping(py::module &mod) {
    py::class_<SimpleGtransfoMapping, std::shared_ptr<SimpleGtransfoMapping>, AstrometryMapping> cls(
            mod, "SimpleGtransfoMapping");
}

void declareSimplePolyMapping(py::module &mod) {
    py::class_<SimplePolyMapping, std::shared_ptr<SimplePolyMapping>, SimpleGtransfoMapping> cls(
            mod, "SimplePolyMapping");
}

PYBIND11_PLUGIN(astrometryMappings) {
    py::module::import("lsst.jointcal.star");
    py::module::import("lsst.jointcal.gtransfo");
    py::module mod("astrometryMappings");

    declareAstrometryMapping(mod);
    declareTwoTransfoMapping(mod);
    declareSimpleGtransfoMapping(mod);
    declareSimplePolyMapping(mod);

    return mod.ptr();
}
}  // namespace
}  // namespace jointcal
}  // namespace lsst
