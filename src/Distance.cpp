#define _USE_MATH_DEFINES
#include <cmath>
#include "Distance.hpp"


using namespace distances;

double EuclDist::compute_distance(const Vec& P1, const Vec& P2) const{
  return ((P1-P2).norm());
}

// OLD FORMULA: great circle distance (commented 3/9/18)
// double Geodist::operator()(const Point& P1, const Point& P2){
//   // Great-circle distance
//   double coeff = M_PI_2/90;
//   double lat1 =  P1(1);
//   double long1 =  P1(2);
//   double lat2 =  P2(1);
//   double long2 =  P2(2);
//   double cos_angle = sin(lat1*coeff)*sin(lat2*coeff)+cos(lat1*coeff)*cos(lat2*coeff)*cos(cmath::abs(long2-long1)*coeff);
//
//   if (cmath::abs(cos_angle-1) < 2*eps_dbl)
//     return (0);
//   else if (cmath::abs(cos_angle+1) < 2*eps_dbl)
//     return (Earth_R * M_PI);
//   else
//     return (Earth_R*acos(cos_angle));
//
// }

// Haversine formula (To be tested)
double GeoDist::compute_distance(const Vec& P1, const Vec& P2) const{
  double coeff = M_PI_2/90;
  double lat1 =  P1(0);
  double long1 =  P1(1);
  double lat2 =  P2(0);
  double long2 =  P2(1);
  double sin_1(sin( (lat2-lat1)/2*coeff ));
  double sin_2((sin( (long2-long1)/2*coeff )));
  double sqrth(sqrt( sin_1*sin_1 + cos(lat1*coeff)*cos(lat2*coeff)* sin_2*sin_2 ));

  if (sqrth > 1) sqrth = 1;

  return (2*Earth_R*asin(sqrth));

}

std::shared_ptr<const MatrixXd> Distance::create_distance_matrix(const Coordinates & coordinates, unsigned int N) const{
  const std::shared_ptr<const MatrixXd> coords = coordinates.get_coords();

  MatrixXd distance_matrix(N, N);
  distance_matrix.fill(0);
  for (size_t i=0; i<(N-1); i++ ) {
    for (size_t j=(i+1); j<N; j++ ) {
      distance_matrix(i,j)=compute_distance(coords->row(i), coords->row(j));
      distance_matrix(j,i)=distance_matrix(i,j);
    }
  }

  return (std::make_shared<const MatrixXd> (distance_matrix));
}

Vec Distance::create_distance_vector(const Coordinates & coordinates, const Vec & new_coord) const{
  unsigned int N(coordinates.get_N_station());

  const std::shared_ptr<const MatrixXd> coords = coordinates.get_coords();

  Vec distance_vector(N);
  for (size_t i=0; i<N; i++) {
    distance_vector(i) = compute_distance(coords->row(i), new_coord);
  }
  return (distance_vector);
}
