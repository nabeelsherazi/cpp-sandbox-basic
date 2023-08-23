#include <random>

class Estimator
{
public:
  Estimator();
  ~Estimator();

  void setSeed(int seed);
  void setNumSamples(int numSamples);
  void setNumDimensions(int numDimensions);
  void setNumThreads(int numThreads);

  void estimate();

  double getPi() const;

private:
  void estimateThread(std::mt19937& generator, std::uniform_real_distribution<double>& distribution, int numSamples);

  int m_seed;
  int m_numSamples;
  int m_numDimensions;
  int m_numThreads;
  double m_pi;

  int m_numSamplesInCircle;
};