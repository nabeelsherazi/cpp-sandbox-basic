#include <thread>
#include <random>
#include <pthread.h>
#include "estimator.hpp"

Estimator::Estimator() : m_seed(0), m_numSamples(0), m_numDimensions(0), m_numThreads(0), m_pi(0.0)
{
}

Estimator::~Estimator()
{
}

void Estimator::setSeed(int seed)
{
  m_seed = seed;
}

void Estimator::setNumSamples(int numSamples)
{
  m_numSamples = numSamples;
}

void Estimator::setNumDimensions(int numDimensions)
{
  m_numDimensions = numDimensions;
}

void Estimator::setNumThreads(int numThreads)
{
  m_numThreads = numThreads;
}

void Estimator::estimate()
{
  std::mt19937 generator(m_seed);
  std::uniform_real_distribution<double> distribution(0.0, 1.0);

  int numSamplesPerThread = m_numSamples / m_numThreads;
  int numSamplesLastThread = numSamplesPerThread + m_numSamples % m_numThreads;

  std::vector<std::thread> threads;
  for (int i = 0; i < m_numThreads; ++i)
  {
    int numSamples = (i == m_numThreads - 1) ? numSamplesLastThread : numSamplesPerThread;
    threads.push_back(
        std::thread(&Estimator::estimateThread, this, std::ref(generator), std::ref(distribution), numSamples));
  }

  for (auto& thread : threads)
  {
    thread.join();
  }

  m_pi = 4.0 * m_numSamplesInCircle / m_numSamples;
}

double Estimator::getPi() const
{
  return m_pi;
}

void Estimator::estimateThread(std::mt19937& generator, std::uniform_real_distribution<double>& distribution,
                               int numSamples)
{
  int numSamplesInCircle = 0;
  for (int i = 0; i < numSamples; ++i)
  {
    double x = distribution(generator);
    double y = distribution(generator);

    if (x * x + y * y <= 1.0)
    {
      ++numSamplesInCircle;
    }
  }

  m_numSamplesInCircle += numSamplesInCircle;
}
