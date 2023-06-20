#ifndef GLMNET_RIDGE_H
#define GLMNET_RIDGE_H
#include "common_headers.h"

#include "smoothPenalty.h"
#include "enet.h" // for definition of tuning parameters

namespace lessSEM
{
  /**
   * @brief ridge penalty for glmnet optimizer
   *
   * The penalty function is given by:
   * $$p( x_j) = \lambda x_j^2$$
   * Note that ridge regularization will not set any of the parameters to zero
   * but result in a shrinkage towards zero.
   *
   * Ridge regularization:
   *
   * * Hoerl, A. E., & Kennard, R. W. (1970). Ridge Regression: Biased Estimation
   * for Nonorthogonal Problems. Technometrics, 12(1), 55–67.
   * https://doi.org/10.1080/00401706.1970.10488634
   */
  class penaltyRidgeGlmnet : public smoothPenalty<tuningParametersEnetGlmnet>
  {
  public:
    /**
     * @brief Get the value of the penalty function
     *
     * @param parameterValues current parameter values
     * @param parameterLabels names of the parameters
     * @param tuningParameters values of the tuning parmameters
     * @return double
     */
    double getValue(const arma::rowvec &parameterValues,
                    const stringVector &parameterLabels,
                    const tuningParametersEnetGlmnet &tuningParameters) override
    {
      // if ridge is not used:
      if (arma::sum(tuningParameters.alpha) == tuningParameters.alpha.n_elem)
        return (0.0);

      // else
      double penalty = 0.0;
      double lambda_i;

      for (unsigned int p = 0; p < parameterValues.n_elem; p++)
      {

        lambda_i = (1.0 - tuningParameters.alpha.at(p)) *
                   tuningParameters.lambda.at(p) *
                   tuningParameters.weights.at(p);

        penalty += lambda_i * std::pow(parameterValues.at(p), 2);
      }

      return penalty;
    }

    /**
     * @brief Get the gradients of the penalty function
     *
     * @param parameterValues current parameter values
     * @param parameterLabels names of the parameters
     * @param tuningParameters values of the tuning parmameters
     * @return arma::rowvec
     */
    arma::rowvec getGradients(const arma::rowvec &parameterValues,
                              const stringVector &parameterLabels,
                              const tuningParametersEnetGlmnet &tuningParameters) override
    {

      arma::rowvec gradients(parameterValues.n_elem);
      gradients.fill(0.0);
      // if ridge is not used:
      if (arma::sum(tuningParameters.alpha) == tuningParameters.alpha.n_elem)
        return (gradients);

      // else

      double lambda_i;

      for (unsigned int p = 0; p < parameterValues.n_elem; p++)
      {

        lambda_i = (1.0 - tuningParameters.alpha.at(p)) *
                   tuningParameters.lambda.at(p) *
                   tuningParameters.weights.at(p);

        gradients.at(p) = lambda_i *
                          2 *
                          parameterValues.at(p);
      }

      return gradients;
    }
  };

}
#endif
