<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns="http://www.devhelp.net/book"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <!--
  Copyright (c) 2009  Daniel Elstner <daniel.kitta@gmail.com>

  XSL transformation from a Doxygen tag file to DevHelp 2 format.

  This script is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation, either version 2 of the License,
  or (at your option) any later version.

  This script is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this script.  If not, see <http://www.gnu.org/licenses/>.
  -->
  <xsl:strip-space elements="*"/>
  <xsl:output method="xml" version="1.0" indent="yes" encoding="UTF-8"/>

  <xsl:param name="book_title"/>
  <xsl:param name="book_name"/>
  <xsl:param name="book_base"/>

  <!-- Define keys to filter compounds that are members of other compounds -->
  <xsl:key name="nested-group" match="compound[@kind='group']" use="subgroup"/>
  <xsl:key name="nested-scope" match="compound[@kind='namespace']" use="namespace|class"/>
  <xsl:key name="nested-scope" match="compound[@kind='class' or @kind='struct' or @kind='union']"
           use="class"/>

  <xsl:template match="/">
    <book title="{$book_title}" name="{$book_name}" base="{$book_base}"
          link="index.html" version="2" language="c++">
      <chapters>
        <xsl:variable name="modules" select="tagfile/compound[@kind='group']"/>
        <xsl:if test="$modules">
          <sub name="Modules" link="modules.html">
            <!-- Select the top-level group compounds -->
            <xsl:apply-templates select="$modules[not(key('nested-group', name))]"
                                 mode="module-list">
              <xsl:sort lang="en" select="title"/>
            </xsl:apply-templates>
          </sub>
        </xsl:if>
        <xsl:variable name="namespaces" select="tagfile/compound[@kind='namespace']"/>
        <xsl:if test="$namespaces">
          <sub name="Namespaces" link="namespaces.html">
            <!-- Generate a flat list of fully qualified namespaces -->
            <xsl:for-each select="$namespaces">
              <xsl:sort lang="en" case-order="upper-first" select="name"/>
              <sub name="{name}" link="{filename}"/>
            </xsl:for-each>
          </sub>
        </xsl:if>
        <xsl:if test="tagfile/compound[@kind='class' or @kind='struct' or @kind='union']">
          <sub name="Classes" link="classes.html">
            <!-- Select the top-level C++ compounds -->
            <xsl:apply-templates select="tagfile/compound[not(key('nested-scope', name))]"
                                 mode="class-list">
              <xsl:sort lang="en" case-order="upper-first" select="name"/>
            </xsl:apply-templates>
          </sub>
        </xsl:if>
      </chapters>
      <functions>
        <xsl:apply-templates select="tagfile/compound" mode="keyword-list"/>
      </functions>
    </book>
  </xsl:template>

  <xsl:template match="compound" mode="module-list">
    <xsl:variable name="children" select="subgroup"/>
    <sub name="{title}" link="{filename}">
      <!-- Select any subgroup compounds by name -->
      <xsl:apply-templates select="../compound[@kind='group' and name=$children]"
                           mode="module-list">
        <xsl:sort lang="en" select="title"/>
      </xsl:apply-templates>
    </sub>
  </xsl:template>

  <xsl:template match="compound[@kind='namespace' or @kind='class' or @kind='struct' or @kind='union']"
                mode="class-list">
    <!-- The scope prefix to strip from the name -->
    <xsl:param name="scope"/>
    <xsl:variable name="fullname" select="name"/>
    <xsl:variable name="children" select="namespace|class"/>
    <sub name="{substring-after($fullname, $scope)}" link="{filename}">
      <!-- Select any nested C++ compounds by name -->
      <xsl:apply-templates select="../compound[name=$children]" mode="class-list">
        <xsl:sort lang="en" case-order="upper-first" select="name"/>
        <xsl:with-param name="scope" select="concat($fullname, '::')"/>
      </xsl:apply-templates>
    </sub>
  </xsl:template>
  <!-- Ignore any other kind of compound -->
  <xsl:template match="*" mode="class-list"/>

  <xsl:template match="compound[@kind='namespace']" mode="keyword-list">
    <!-- Process members, but do not list the namespace itself as a keyword -->
    <xsl:apply-templates select="member" mode="keyword-list"/>
  </xsl:template>
  <xsl:template match="compound[@kind='class' or @kind='struct' or @kind='union']"
                mode="keyword-list">
    <!-- List the compound type itself as a keyword and process its members -->
    <keyword type="struct" name="{name}" link="{filename}"/>
    <xsl:apply-templates select="member" mode="keyword-list"/>
  </xsl:template>
  <!-- Match leaf compound members -->
  <xsl:template match="member[@kind='typedef']" mode="keyword-list">
    <keyword type="typedef" xsl:use-attribute-sets="keyword-member"/>
  </xsl:template>
  <xsl:template match="member[@kind='function' or @kind='friend']" mode="keyword-list">
    <keyword type="function" xsl:use-attribute-sets="keyword-member"/>
  </xsl:template>
  <xsl:template match="member[@kind='enumeration']" mode="keyword-list">
    <keyword type="enum" xsl:use-attribute-sets="keyword-member"/>
  </xsl:template>
  <xsl:template match="member[@kind='enumvalue' or @kind='define']" mode="keyword-list">
    <keyword type="macro" xsl:use-attribute-sets="keyword-member"/>
  </xsl:template>
  <!-- Ignore unknown keyword types -->
  <xsl:template match="*" mode="keyword-list"/>

  <!-- Qualify member name and link anchor -->
  <xsl:attribute-set name="keyword-member">
    <xsl:attribute name="name">
      <xsl:value-of select="concat(../name, '::', name)"/>
    </xsl:attribute>
    <xsl:attribute name="link">
      <xsl:value-of select="concat(anchorfile, '#', anchor)"/>
    </xsl:attribute>
  </xsl:attribute-set>

</xsl:stylesheet>
