#include <airmap/codec/json/geometry.h>

#include <airmap/codec.h>
#include <airmap/codec/json/get.h>

void airmap::codec::json::decode(const nlohmann::json& j, Geometry& g) {
  auto type = j["type"].get<Geometry::Type>();

  switch (type) {
    case Geometry::Type::point: {
      g = Geometry{j["coordinates"].get<Geometry::Point>()};
      break;
    }
    case Geometry::Type::multi_point: {
      g = Geometry{j["coordinates"].get<Geometry::MultiPoint>()};
      break;
    }
    case Geometry::Type::line_string: {
      g = Geometry{j["coordinates"].get<Geometry::LineString>()};
      break;
    }
    case Geometry::Type::multi_line_string: {
      g = Geometry{j["coordinates"].get<Geometry::MultiLineString>()};
      break;
    }
    case Geometry::Type::polygon: {
      g = Geometry{j["coordinates"].get<Geometry::Polygon>()};
      break;
    }
    case Geometry::Type::multi_polygon: {
      g = Geometry{j["coordinates"].get<Geometry::MultiPolygon>()};
      break;
    }
    case Geometry::Type::geometry_collection: {
      g = Geometry{j["coordinates"].get<Geometry::GeometryCollection>()};
      break;
    }
    default:
      break;
  }
}

void airmap::codec::json::decode(const nlohmann::json& j, std::vector<Geometry>& v) {
  for (auto element : j) {
    v.push_back(Geometry{});
    v.back() = element;
  }
}

void airmap::codec::json::decode(const nlohmann::json& j, Geometry::Type& t) {
  const auto& type_string = j.get<std::string>();

  if (type_string == "Point")
    t = Geometry::Type::point;
  else if (type_string == "MultiPoint")
    t = Geometry::Type::multi_point;
  else if (type_string == "LineString")
    t = Geometry::Type::line_string;
  else if (type_string == "MultiLineString")
    t = Geometry::Type::multi_line_string;
  else if (type_string == "Polygon")
    t = Geometry::Type::polygon;
  else if (type_string == "MultiPolygon")
    t = Geometry::Type::multi_polygon;
  else if (type_string == "GeometryCollection")
    t = Geometry::Type::geometry_collection;
}

void airmap::codec::json::decode(const nlohmann::json& j, Geometry::Coordinate& c) {
  c.latitude  = j.at(1).get<float>();
  c.longitude = j.at(0).get<float>();
  if (j.size() > 2)
    c.altitude = j.at(2).get<float>();
}

void airmap::codec::json::decode(const nlohmann::json& j, Geometry::MultiLineString& mls) {
  for (const auto& element : j) {
    mls.push_back(Geometry::LineString{});
    mls.back() = element;
  }
}

void airmap::codec::json::decode(const nlohmann::json& j, Geometry::Polygon& p) {
  for (const auto& element : j) {
    p.push_back(Geometry::CoordinateVector<Geometry::Type::polygon>{});
    p.back() = element;
  }
}

void airmap::codec::json::decode(const nlohmann::json& j, Geometry::MultiPolygon& mp) {
  for (const auto& element : j) {
    mp.push_back(Geometry::Polygon{});
    mp.back() = element.get<Geometry::Polygon>();
  }
}

void airmap::codec::json::encode(nlohmann::json& j, const Geometry& geometry) {
  j["type"] = geometry.type();
  switch (geometry.type()) {
    case Geometry::Type::point:
      j["coordinates"] = geometry.details_for_point();
      break;
    case Geometry::Type::multi_point:
      j["coordinates"] = geometry.details_for_multi_point();
      break;
    case Geometry::Type::line_string:
      j["coordinates"] = geometry.details_for_line_string();
      break;
    case Geometry::Type::multi_line_string:
      j["coordinates"] = geometry.details_for_multi_line_string();
      break;
    case Geometry::Type::polygon:
      j["coordinates"] = geometry.details_for_polygon();
      break;
    case Geometry::Type::multi_polygon:
      j["coordinates"] = geometry.details_for_multi_polygon();
      break;
    case Geometry::Type::geometry_collection:
      j["coordinates"] = geometry.details_for_geometry_collection();
      break;
    default:
      break;
  }
}

void airmap::codec::json::encode(nlohmann::json& j, const std::vector<Geometry>& geometries) {
  for (const auto& geometry : geometries)
    j.push_back(geometry);
}

void airmap::codec::json::encode(nlohmann::json& j, Geometry::Type type) {
  switch (type) {
    case Geometry::Type::point:
      j = "Point";
      break;
    case Geometry::Type::multi_point:
      j = "MultiPoint";
      break;
    case Geometry::Type::line_string:
      j = "LineString";
      break;
    case Geometry::Type::multi_line_string:
      j = "MultiLineString";
      break;
    case Geometry::Type::polygon:
      j = "Polygon";
      break;
    case Geometry::Type::multi_polygon:
      j = "MultiPolygon";
      break;
    case Geometry::Type::geometry_collection:
      j = "GeometryCollection";
      break;
    default:
      break;
  }
}

void airmap::codec::json::encode(nlohmann::json& j, const Geometry::Coordinate& coordinate) {
  j.push_back(coordinate.longitude);
  j.push_back(coordinate.latitude);
  if (coordinate.altitude)
    j.push_back(coordinate.altitude.get());
  if (coordinate.elevation)
    j.push_back(coordinate.elevation.get());
}

void airmap::codec::json::encode(nlohmann::json& j, const std::vector<Geometry::Coordinate>& coordinates) {
  for (const auto& coordinate : coordinates)
    j.push_back(coordinate);
}

void airmap::codec::json::encode(nlohmann::json& j, const std::vector<Geometry::Polygon>& cvs) {
  for (const auto& cv : cvs)
    j.push_back(cv);
}