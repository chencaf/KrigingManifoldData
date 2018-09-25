#ifndef _MAPFUNCTIONS_HPP_
#define _MAPFUNCTIONS_HPP_
#include <memory>

#include "DistanceManifold.hpp"

namespace map_functions {

// LOGARITHMIC MAP
  class logarithmicMap{
  public:
    // logarithmicMap(const distances_manifold::DistanceManifold&);
    virtual MatrixXd map2tplane(const MatrixXd&) const = 0;
    virtual void initialize_members(const std::shared_ptr<const MatrixXd>) = 0;
  };

  class logMapFrob : public logarithmicMap{
    MatrixXd  _sqrtSigma;
    MatrixXd  _sqrtSigmaInv;
  public:
    MatrixXd map2tplane(const MatrixXd&) const override;
    void initialize_members(const std::shared_ptr<const MatrixXd>) override;
  };

  class logMapLogEucl : public logarithmicMap{
    std::shared_ptr<const MatrixXd> _Sigma;
  public:
    MatrixXd map2tplane(const MatrixXd&) const override;
    void initialize_members(const std::shared_ptr<const MatrixXd>) override;
  };

  class logMapSqRoot : public logarithmicMap{
    std::shared_ptr<const MatrixXd> _Sigma;
  public:
    MatrixXd map2tplane(const MatrixXd&) const override;
    void initialize_members(const std::shared_ptr<const MatrixXd>) override;
  };



  // EXPONENTIAL MAP

  class exponentialMap{
  public:
    virtual MatrixXd map2manifold(const MatrixXd&) const = 0;
    virtual void initialize_members(const std::shared_ptr<const MatrixXd>) = 0;

  };


  class expMapFrob : public exponentialMap{
    MatrixXd _sqrtSigma;
    MatrixXd _sqrtSigmaInv;
  public:
    MatrixXd map2manifold(const MatrixXd&) const override;
    void initialize_members(const std::shared_ptr<const MatrixXd>) override;

  };

  class expMapLogEucl : public exponentialMap{
    std::shared_ptr<const MatrixXd> _Sigma;
  public:
    MatrixXd map2manifold(const MatrixXd&) const override;
    void initialize_members(const std::shared_ptr<const MatrixXd>) override;
  };

  class expMapSqRoot : public exponentialMap{
    std::shared_ptr<const MatrixXd> _Sigma;
  public:
    MatrixXd map2manifold(const MatrixXd&) const override;
    void initialize_members(const std::shared_ptr<const MatrixXd>) override;
  };


}


#endif
