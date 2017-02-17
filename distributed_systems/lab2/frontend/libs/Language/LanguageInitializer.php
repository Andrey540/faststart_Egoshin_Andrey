<?php

    class LanguageInitializer
    {
        const RU = 'ru';
        const EN = 'en';

        const DEFAULT_LANGUAGE = self::EN;

        private static $currentLanguage = self::DEFAULT_LANGUAGE;

        public static function initLanguage($container, $language)
        {
            static $localizations = [
                self::RU => 'ru_RU',
                self::EN => 'en_US'
            ];

            if (!isset($localizations[$language]))
            {
                $language = 'en';
            }
            $locale = $localizations[$language];

            $translator = null;
            $view = $container['view'];
            foreach ($view->getEnvironment()->getExtensions() as $extension)
            {
                if ($extension instanceof Symfony\Bridge\Twig\Extension\TranslationExtension)
                {
                    $translator = $extension->getTranslator();
                    break;
                }
            }
            if ($translator)
            {
                $translator->setLocale($locale);
            }
            self::$currentLanguage = $language;
        }

        public static function getCurrentLanguage()
        {
            return self::$currentLanguage;
        }
    }