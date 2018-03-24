// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2009-2010 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// This Source Code Form is subject to the terms of the Mozilla
// Public License v. 2.0. If a copy of the MPL was not distributed
// with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HYDRA_EIGEN_FORCEALIGNEDACCESS_H
#define HYDRA_EIGEN_FORCEALIGNEDACCESS_H

HYDRA_EXTERNAL_NAMESPACE_BEGIN namespace Eigen {

/** \class ForceAlignedAccess
  * \ingroup Core_Module
  *
  * \brief Enforce aligned packet loads and stores regardless of what is requested
  *
  * \param ExpressionType the type of the object of which we are forcing aligned packet access
  *
  * This class is the return type of MatrixBase::forceAlignedAccess()
  * and most of the time this is the only way it is used.
  *
  * \sa MatrixBase::forceAlignedAccess()
  */

namespace internal {
template<typename ExpressionType>
struct traits<ForceAlignedAccess<ExpressionType> > : public traits<ExpressionType>
{};
}

template<typename ExpressionType> class ForceAlignedAccess
  : public internal::dense_xpr_base< ForceAlignedAccess<ExpressionType> >::type
{
  public:

    typedef typename internal::dense_xpr_base<ForceAlignedAccess>::type Base;
    HYDRA_EIGEN_DENSE_PUBLIC_INTERFACE(ForceAlignedAccess)

    HYDRA_EIGEN_DEVICE_FUNC explicit inline ForceAlignedAccess(const ExpressionType& matrix) : m_expression(matrix) {}

    HYDRA_EIGEN_DEVICE_FUNC inline Index rows() const { return m_expression.rows(); }
    HYDRA_EIGEN_DEVICE_FUNC inline Index cols() const { return m_expression.cols(); }
    HYDRA_EIGEN_DEVICE_FUNC inline Index outerStride() const { return m_expression.outerStride(); }
    HYDRA_EIGEN_DEVICE_FUNC inline Index innerStride() const { return m_expression.innerStride(); }

    HYDRA_EIGEN_DEVICE_FUNC inline const CoeffReturnType coeff(Index row, Index col) const
    {
      return m_expression.coeff(row, col);
    }

    HYDRA_EIGEN_DEVICE_FUNC inline Scalar& coeffRef(Index row, Index col)
    {
      return m_expression.const_cast_derived().coeffRef(row, col);
    }

    HYDRA_EIGEN_DEVICE_FUNC inline const CoeffReturnType coeff(Index index) const
    {
      return m_expression.coeff(index);
    }

    HYDRA_EIGEN_DEVICE_FUNC inline Scalar& coeffRef(Index index)
    {
      return m_expression.const_cast_derived().coeffRef(index);
    }

    template<int LoadMode>
    inline const PacketScalar packet(Index row, Index col) const
    {
      return m_expression.template packet<Aligned>(row, col);
    }

    template<int LoadMode>
    inline void writePacket(Index row, Index col, const PacketScalar& x)
    {
      m_expression.const_cast_derived().template writePacket<Aligned>(row, col, x);
    }

    template<int LoadMode>
    inline const PacketScalar packet(Index index) const
    {
      return m_expression.template packet<Aligned>(index);
    }

    template<int LoadMode>
    inline void writePacket(Index index, const PacketScalar& x)
    {
      m_expression.const_cast_derived().template writePacket<Aligned>(index, x);
    }

    HYDRA_EIGEN_DEVICE_FUNC operator const ExpressionType&() const { return m_expression; }

  protected:
    const ExpressionType& m_expression;

  private:
    ForceAlignedAccess& operator=(const ForceAlignedAccess&);
};

/** \returns an expression of *this with forced aligned access
  * \sa forceAlignedAccessIf(),class ForceAlignedAccess
  */
template<typename Derived>
inline const ForceAlignedAccess<Derived>
MatrixBase<Derived>::forceAlignedAccess() const
{
  return ForceAlignedAccess<Derived>(derived());
}

/** \returns an expression of *this with forced aligned access
  * \sa forceAlignedAccessIf(), class ForceAlignedAccess
  */
template<typename Derived>
inline ForceAlignedAccess<Derived>
MatrixBase<Derived>::forceAlignedAccess()
{
  return ForceAlignedAccess<Derived>(derived());
}

/** \returns an expression of *this with forced aligned access if \a Enable is true.
  * \sa forceAlignedAccess(), class ForceAlignedAccess
  */
template<typename Derived>
template<bool Enable>
inline typename internal::add_const_on_value_type<typename internal::conditional<Enable,ForceAlignedAccess<Derived>,Derived&>::type>::type
MatrixBase<Derived>::forceAlignedAccessIf() const
{
  return derived();  // FIXME This should not work but apparently is never used
}

/** \returns an expression of *this with forced aligned access if \a Enable is true.
  * \sa forceAlignedAccess(), class ForceAlignedAccess
  */
template<typename Derived>
template<bool Enable>
inline typename internal::conditional<Enable,ForceAlignedAccess<Derived>,Derived&>::type
MatrixBase<Derived>::forceAlignedAccessIf()
{
  return derived();  // FIXME This should not work but apparently is never used
}

} /* end namespace Eigen */  HYDRA_EXTERNAL_NAMESPACE_END

#endif // HYDRA_EIGEN_FORCEALIGNEDACCESS_H