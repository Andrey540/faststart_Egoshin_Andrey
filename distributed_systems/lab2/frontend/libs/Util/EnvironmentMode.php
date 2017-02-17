<?
namespace Util;

class EnvironmentMode
{
    const PROD = 'production';
    const DEV = 'development';

    public static function isProdEnv()
    {
        return $_ENV['SLIM_MODE'] == self::PROD;
    }
}